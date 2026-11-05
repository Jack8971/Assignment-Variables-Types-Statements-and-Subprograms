//[ORIGINAL]
//Check if the header file has already been included
#ifndef DATE_H
#define DATE_H

//Extra libraries needed for the Date class
#include <optional>
#include <string>

// Immutable calendar date (value type). A Date object is always a real date and not a duplicate.
class Date {
public://All public methods are declared here

    //Constructor
    // Throws std::invalid_argument if the date does not exist (e.g. 2023-02-30).
    Date(int year, int month, int day);

    // Parses "YYYY-MM-DD". Returns std::nullopt instead of throwing,
    // so callers can validate user input without try/catch.
    static std::optional<Date> parse(const std::string& text);

    // Current local date.
    static Date today();

    // Returns true if 'year' is a leap year.
    static bool isLeapYear(int year);
    // Returns the number of days in 'month' of 'year'.
    static int daysInMonth(int year, int month);

    int year() const;
    int month() const;
    int day() const;

    // Whole years completed between this date and 'reference'.
    int ageOn(const Date& reference) const;

    // "YYYY-MM-DD"
    std::string toString() const;

    // Comparison overloaded operators
    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;

private://All private methods are declared here
    int year_;
    int month_;
    int day_;
};

#endif // DATE_H