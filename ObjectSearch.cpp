#include "ObjectSearch.h"
#include "DerivedClass.h"
#include "BaseClass.h"
#include <cmath>

bool findEqualPolyEval(BaseClass* instancesToCheck, int numberOfInstances,
                       BaseClass* instanceToFind, int polyEvalPoint){
    int polyToFind, polyToCheck;
    polyToFind=instanceToFind->evaluateAsPolynomial(polyEvalPoint);
    int first=0, last=numberOfInstances-1;
    int middle;
    while (first<last-1)//make sure that there are at least 3 memebers left---> to make sure middle point exist
    {
       middle=floor((first+last)/2); 
       polyToCheck=(instancesToCheck+middle)->evaluateAsPolynomial(polyEvalPoint);
       
       if (polyToCheck == polyToFind)
          return true;
       else
       {
          if (polyToCheck > polyToFind)
          {
             last=middle;
          }
          else if (polyToCheck < polyToFind)
          {
             first=middle;
          }
      }
    }
    
    //There is possibility that the first and last member is not check, so check them here
    //The last member
    polyToCheck=(instancesToCheck+numberOfInstances-1)->evaluateAsPolynomial(polyEvalPoint);
    if (polyToCheck == polyToFind)
          return true;
    //The first memeber
    polyToCheck=(instancesToCheck)->evaluateAsPolynomial(polyEvalPoint);
    if (polyToCheck == polyToFind)
          return true;

    return false;

}
