#ifndef __EMPLOYEE__
#define __EMPLOYEE__

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

enum DATA_FIELDS
{
	NAME, STATUS, SALARY, PAY_BASIS, POSITION
};

class Employee{
	public:
		Employee();
		Employee(std::string fileLine);
		
		void setField(DATA_FIELDS dataField, std::string value);

		std::string name_;
		std::string status_;
		double salary_;
		std::string payBasis_;
		std::string positionTitle_;

	friend std::ostream& operator<<(std::ostream&, const Employee&);

};

class CompareClass
{
        private:
   DATA_FIELDS dataField_;
   bool isAscending_;

	public:
   CompareClass(DATA_FIELDS dataField, bool isAscending=true) : dataField_(dataField), isAscending_(isAscending){}
   // TODO: Part2: implement the overloaded () operator. 
   bool operator() (Employee *pX, Employee *pY) {
      bool results=false;
      if (isAscending_)
      {
         switch(dataField_){
          case NAME:
            if(pX->name_ < pY->name_)
               results = true;
            else
               results = false;
            break;
          case STATUS:
            if(pX->status_< pY->status_)
               results = true;
            else
               results =  false;
            break;
          case SALARY:
            if(pX->salary_ < pY->salary_)
               results =  true;
            else
               results =  false;  
            break;
          case PAY_BASIS:
            if(pX->payBasis_ < pY->payBasis_)
               results =  true;
            else
               results =  false;
            break;
          case POSITION:
            if(pX->positionTitle_ < pY->positionTitle_)
               results =  true;
            else
               results =  false;
            break;
         }
      }
      else
      {
         switch(dataField_){
          case NAME:
            if(pX->name_ > pY->name_)
               results =  true;
            else
               results =  false;
            break;
          case STATUS:
            if(pX->status_ > pY->status_)
               results =  true;
            else
               results =  false;
            break;
          case SALARY:
            if(pX->salary_ > pY->salary_)
               results =  true;
            else
               results =  false;
            break;
          case PAY_BASIS:
            if(pX->payBasis_ > pY->payBasis_)
               results =  true;
            else
               results =  false;
            break;
          case POSITION:
            if(pX->positionTitle_ > pY->positionTitle_)
               results =  true;
            else
               results =  false;
            break;
         }
      }
   return results;
   }
//	private:
   //DATA_FIELDS dataField_;
   //bool isAscending_;
};
std::ostream& operator<<(std::ostream &strm, const Employee &emp);

std::string getEmployeeFileHeader();
#endif
