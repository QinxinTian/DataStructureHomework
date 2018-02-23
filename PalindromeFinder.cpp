#include "PalindromeFinder.h"
#include <string>
#include <iostream>

#include <sstream>
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

using namespace std;

PalindromeFinder::PalindromeFinder(){}

string PalindromeFinder::toString(){
    return "largest palindrome seen so far is \"" + this->getLargestPalindromeFound() +
           "\" with size " + patch::to_string(this->getSizeOfLargestPalindromeFound());
}

string PalindromeFinder::getLargestPalindromeFound(){
    return this->largestPalindromeFound;
}

int PalindromeFinder::getSizeOfLargestPalindromeFound(){
    return this->largestPalindromeFound.length();
}

//returns true if input is a palindrome, false otherwise. If it is a palindrome and
// it is the largest seen so far, it should be stored in largestPalindromeFound.
bool PalindromeFinder::isPalindrome(string input){
    //TODO define isPalindrome with the desired functionality
    int i = 0;
    int j = input.length() - 1;
    while(i<j){
      if(!(input.at(i) == input.at(j))){
        return false;
      }
      i++;
      j--;
    }
    if(this->largestPalindromeFound.length() < input.length()){
        this->largestPalindromeFound = input;
    }
    return true;
}

//Returns the largest palindrome in the string array inputStrings. If this is the
// the largest palindrome seen, this instance of the class should store it in
// largestPalindromeFound.
string PalindromeFinder::getLargestPalindrome(string* inputStrings, int numberOfStrings){
    //TODO Debug getLargestPalindrome so it outputs the proper string and updates largestPalindromeFound
    string largestPalindrome = "";
    for(int i=0; i<numberOfStrings; i++){
        if(this->isPalindrome(*(inputStrings+i))){
            largestPalindrome = *(inputStrings+i);
            this->truncateToLargestPalindrome(largestPalindrome);
        }
    }
    return this->largestPalindromeFound;
}

//truncates the input string to its largest substring that is a palindrome.
// If this palindrome is the biggest seen so far, the class should store it
// in largestPalindromeFound.
void PalindromeFinder::truncateToLargestPalindrome(string& inputString){
    //TODO define truncateToLargestPalindrome with the proper functionality
    if(this->largestPalindromeFound.length() < inputString.length()){
        this->largestPalindromeFound = inputString;
    }
}