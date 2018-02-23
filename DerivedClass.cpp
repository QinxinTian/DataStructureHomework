#include <algorithm>
#include "DerivedClass.h"
#include "BaseClass.h"
#include <cmath>

int DerivedClass::findClosestToZero() {
    return this->findClosestToZero(this->numberOfValues-1);
}

int DerivedClass::findClosestToZero(int n) {
    int distance = std::max(this->values[n], -this->values[n]);
    n--;//make sure that n is from 0 ~ numberOfValues-1
    int closestDistance;
    if (n==-1){
       return distance;}
    else{
       if(distance < this->findClosestToZero(n)){
           closestDistance = distance;
       }else{
           closestDistance = this->findClosestToZero(n);
       }
       return closestDistance;
    }
}

int DerivedClass::getSum(){
    int sum=0;
    for (int i=0; i<numberOfValues; i++)
    {
        sum += values[i];
    }
   
    return sum;
}


int DerivedClass::getMultiplication(){
    int mul=1;
    
    for (int i=0; i<numberOfValues; i++)
    {
      mul *= values[i];
    }
    
    return mul;  
}

int DerivedClass::evaluateAsPolynomial(int x){
    int sum=0;
    int term;
    for (int i=0; i<numberOfValues; i++)
    {
      term=pow(x, i);
      sum += (values[i]*term);
    }

    return sum;
}
