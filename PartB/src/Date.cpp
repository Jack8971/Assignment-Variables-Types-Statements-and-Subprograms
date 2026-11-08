#include "Date.h" //Include the header file for the Date class

//[EXTERNAL MODIFIED] The document was written by kunj but the comments and auto complete were aided by Copilot.
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

Date::Date(int day, int month, int year)//Constructor and exception handling for invalid dates
    : day_(day), month_(month), year_(year){
        if ( year<1 || month<1 || month>12 || day<1 || day>daysInMonth(year, month) ){
            throw std::invalid_argument("Invalid date");
        }
}

bool Date::isLeapYear(int year){//Check if the year is a leap year
    return ( year%4==0 && year%100!=0)||(year%400==0);
}

int Date::daysInMonth(int year, int month){
    //The number of days in each month, with February having 28 days by default it is kept static so that it is not reallocated every time the function is called
    static const int kDays[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month==2 && isLeapYear(year)) return 29; //If the month is February and it is a leap year, return 29
    return kDays[month-1]; //Return the number of days in the month
}

std::optional<Date> Date::parse(const std::string& text) {//Parse the date from a string in the format "YYYY-MM-DD"
    // Strict format check first: exactly YYYY-MM-DD.
    if (text.size() != 10 || text[4] != '-' || text[7] != '-') {
        return std::nullopt;
    }
    const std::string yearText = text.substr(0, 4);
    const std::string monthText = text.substr(5, 2);
    const std::string dayText = text.substr(8, 2);
    if (!isAllDigits(yearText) || !isAllDigits(monthText) || !isAllDigits(dayText)) {
        return std::nullopt;
    }
    try {
        return Date(std::stoi(yearText), std::stoi(monthText), std::stoi(dayText));
    } catch (const std::invalid_argument&) {
        return std::nullopt; // right shape, but not a real date
    }
}

Date Date::today() {//Get the current local date
    std::time_t now = std::time(nullptr);
    std::tm local{};
#ifdef _WIN32// Windows-specific code to get the local time or else use the POSIX version for other platforms
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif
    return Date(local.tm_year + 1900, local.tm_mon + 1, local.tm_mday);
}

//Getters for the year, month, and day
int Date::year() const { return year_; }
int Date::month() const { return month_; }
int Date::day() const { return day_; }

int Date::ageOn(const Date& reference) const {//Calculate the age on a reference date
    int age = reference.year_ - year_;
    // Birthday has not happened yet in the reference year.
    if (reference.month_ < month_ ||
        (reference.month_ == month_ && reference.day_ < day_)) {
        --age;
    }
    return age;
}

std::string Date::toString() const {//Convert the date to a string in the format "YYYY-MM-DD"
    std::ostringstream out;
    out << std::setfill('0') << std::setw(4) << year_ << '-'
        << std::setw(2) << month_ << '-'
        << std::setw(2) << day_;
    return out.str();
}

bool Date::operator==(const Date& other) const {//Overload the equality operator to compare two Date objects
    return std::tie(year_, month_, day_) ==
           std::tie(other.year_, other.month_, other.day_);
}

bool Date::operator<(const Date& other) const {//Overload the less than operator to compare two Date objects
    return std::tie(year_, month_, day_) <
           std::tie(other.year_, other.month_, other.day_);
}