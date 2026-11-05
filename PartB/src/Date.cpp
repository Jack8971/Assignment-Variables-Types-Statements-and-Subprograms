#include "Date.h" //Include the header file for the Date class

//[EXTERNAL MODIFIED] The include statements were written by me but the comments were done by Copilot.
#include <cctype> //Include the cctype library for character handling functions 
#include <ctime> //Include the ctime library for time functions
#include <iomanip> //Include the iomanip library for input/output manipulators
#include <iostream> //Include the iostream library for input/output stream functions
#include <sstream> //Include the sstream library for string stream functions
#include <stdexcept> //Include the stdexcept library for standard exception handling
#include <tuple> //Include the tuple library for using std::tuple

//namespace for helper functions that are only used within this file
namespace{
    bool isAllDigits(const std::string& str){
        for (char c : str){
            if(!std::isdigit(static_cast<unsigned char>(c)))return false;//Check if the character is not a digit, return false
        }
        return !str.empty();//Edge case: return false if the string is empty, otherwise return true
    }
}

Date::Date(int day, int month, int year)
    : day_(day), month_(month), year_(year){}