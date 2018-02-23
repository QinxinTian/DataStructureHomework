#ifndef CSE250_FALL2015_DERIVEDCLASS_H
#define CSE250_FALL2015_DERIVEDCLASS_H

#include "BaseClass.h"

class DerivedClass : public BaseClass {

private:


public:
    DerivedClass() : BaseClass(){}
    DerivedClass(int* values, int numberOfValues) : BaseClass(values, numberOfValues){}

    virtual int findClosestToZero();
    virtual int findClosestToZero(int);
    virtual int getSum();
    virtual int getMultiplication();
    virtual int evaluateAsPolynomial(int);
    
    //accessor for debugging
    int * giveValue () const
    {
       return values;
    }
};


#endif //CSE250_FALL2015_DERIVEDCLASS_H
