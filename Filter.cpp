#include <iostream> 
#include "Filter.h"
#include <iterator>

using namespace std;

//The basic filter function
void BasicFilter(vector<Employee *> *pEmpVector, pair<string, string> dataLimit, SELECTION_CRITERIA selectCrit, DATA_FIELDS searchField)
{
     //create < compare operator
     bool isAscending = true;
     CompareClass compareClass(searchField, isAscending); //sort should based on firstField_

     vector<Employee *>::iterator low, up;

     string toFindStr=get<0>(dataLimit);
     Employee *toFind = new Employee();
     toFind->setField(searchField, toFindStr);
     
     if (selectCrit==BETWEEN)
     {
        string toFindStr2 = get<1>(dataLimit);
        Employee* toFind2 = new Employee();
        toFind2->setField(searchField, toFindStr2); 

        up=upper_bound(pEmpVector->begin(),pEmpVector->end(),toFind, compareClass);//Returns the first element that larger than toFind
        pEmpVector->erase(pEmpVector->begin(),up);

        low=lower_bound(pEmpVector->begin(),pEmpVector->end(),toFind2, compareClass);//returns the first element which equals to toFind
        pEmpVector->erase(low, pEmpVector->end()); //pay attention to -1 : because pEmpVector->end() points to the boundary of the vector, not the last element in the vector
           return;
     }

     //int i = BinarySearch (pEmpVector->begin(),pEmpVector->end(),toFind, compareClass); // it is cute to use your own BinarySearch ---> but not necessary. Actually, lower_bound and upper_bound if some field have same value
    
     switch (selectCrit)
     {
        case LESS: //I am assuming that LESS means that "give me all employees whose field are less than give value"---> need to be verified
           low=lower_bound(pEmpVector->begin(),pEmpVector->end(),toFind, compareClass);//returns the first element which equals to toFind
           pEmpVector->erase(low, pEmpVector->end()); //pay attention to -1 : because pEmpVector->end() points to the boundary of the vector, not the last element in the vector
           return;
        case GREATER:
           up=upper_bound(pEmpVector->begin(),pEmpVector->end(),toFind, compareClass);//Returns the first element that larger than toFind
           //pEmpVector->erase(pEmpVector->begin(),up-1);
           pEmpVector->erase(pEmpVector->begin(),up);
           return;
        case IS_EQUAL:
           low=lower_bound(pEmpVector->begin(),pEmpVector->end(),toFind, compareClass);//returns the first element which equals to toFind
           up=upper_bound(pEmpVector->begin(),pEmpVector->end(),toFind, compareClass);//Returns the first element that larger than toFind
           //pEmpVector->erase(pEmpVector->begin(),low);
           pEmpVector->erase(pEmpVector->begin(),low);//Why not low-1? I need to figure out---> erase did not erase the last element.
           pEmpVector->erase(up, pEmpVector->end());
           return;
//        case BETWEEN:
//           up=upper_bound(pEmpVector->begin(),pEmpVector->end(),toFind, compareClass);//Returns the first element that larger than toFind
//           pEmpVector->erase(pEmpVector->begin(),up-1);

//           low=lower_bound(pEmpVector->begin(),pEmpVector->end(),toFind2, compareClass);//returns the first element which equals to toFind
//           pEmpVector->erase(low, pEmpVector->end()-1); //pay attention to -1 : because pEmpVector->end() points to the boundary of the vector, not the last element in the vector
//           return;
        default:
           cout << "Invalid selectCrit" <<endl;
           return; //maybe exit() is a better choice
     }
}

Filter::Filter(vector<Employee *> *pEmpVector, DATA_FIELDS field, SELECTION_CRITERIA selectCrit, pair<string, string> dataLimit):
field_(field), firstField_(field), selectCrit_(selectCrit)
{
   // TODO: Part 3. Modify or add code to perform the filtering based on the parameters given. Even the next line!
	pEmpVector_ = pEmpVector;

        //find string_start with binary search ---> if necessary, find string_start end also.    
        BasicFilter(pEmpVector_, dataLimit, selectCrit_, field_);
  
        
}

void Filter::printFilter() //Do I need to modify this part for out put? not sure, let's see
{
   //before print on the screen, need to sort the output based on Name filterType
   cout << getEmployeeFileHeader();
	for (size_t i = 0; i < pEmpVector_->size(); i++)
	{
		cout << *(pEmpVector_->at(i));
	}
}


void Filter::addFilter(vector<Employee *> *pEmpVector, DATA_FIELDS field, SELECTION_CRITERIA selectCrit, pair<string, string> dataLimit, FILTER_TYPE filterType)
{
	// TODO: Part 3.
	
        //find string_start with binary search ---> if necessary, find string_start end also.
        if (filterType==END)
            return;
        else if (filterType==FIRST)
        {
            cout<<"It is not necessary to add filter as your filterType==FIRST!" <<endl;
            return;
        }
        else
            BasicFilter(pEmpVector, dataLimit, selectCrit, field);

       //merge two Employee table based on filterType --> finally update pEmpVector_ ---> merge should always based on unique id, name
       //Create name-based compare operator <
       bool isAscending = true;          
       CompareClass compareClass(NAME, isAscending); //sort should based on firstField_
   
       //sort both pEmpVector and pEmpVector_
       if (field_) //if dataField_ != 0  -->To avoid repeat sorting of pEmpVector_
       {
         sort(pEmpVector_->begin(), pEmpVector_->end(),compareClass);
         field_ = NAME;
       }
       sort(pEmpVector->begin(), pEmpVector->end(),compareClass);
      
       //merge process
       vector<Employee *> tempVector(pEmpVector->size()+pEmpVector_->size()); //The size of this vector should be large enough---> One bug was found here
       //tempVector.reserve(pEmpVector->size()); //allocate max memory space
       vector<Employee *> :: iterator itr;
       if (filterType == AND)
       {
          //itr=set_intersection(pEmpVector_->begin(), pEmpVector_->end(),pEmpVector->begin(), pEmpVector->end(),back_inserter(tempVector), compareClass);
          itr=set_intersection(pEmpVector_->begin(), pEmpVector_->end(),pEmpVector->begin(), pEmpVector->end(),tempVector.begin(), compareClass);
       }
       else if (filterType == OR)
       {
         //itr=set_union(pEmpVector_->begin(), pEmpVector_->end(),pEmpVector->begin(), pEmpVector->end(),back_inserter(tempVector),compareClass);
          itr=set_union(pEmpVector_->begin(), pEmpVector_->end(),pEmpVector->begin(), pEmpVector->end(),tempVector.begin(),compareClass);
       }
       else
         cout << "invalid filterType!" << endl;

       tempVector.resize(itr-tempVector.begin()); //resize the temvector --->to save memory
       pEmpVector_->swap(tempVector); //Better than erase/clear and copy: 1) save time;  2) can guarantee reallocation 
         //pEmpVector_->erase(pEmpVector_->begin(),pEmpVector_->end());
         //copy(tempVector.begin(),tempVector.end(),pEmpVector_->begin());
       
       //Need to make sure the output is ordered based on NAME---> Only necessary for "OR" Filter
       if (filterType == OR)
          sort(pEmpVector_->begin(), pEmpVector_->end(),compareClass);
       
       return;
}  

