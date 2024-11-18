#include "Date.hpp"
#include <stdexcept>

// default constructor: initializes the date to 0/0/0
Date::Date() : year(0), month(0), day(0) {}

// parameterized constructor: initializes the date with provided year, month, and day values
Date::Date(short int year, short int month, short int day)
    : year(year), month(month), day(day) {}

// setter for year with validation to ensure it is a positive value
void Date::setYear(short int newYear) {
    if (newYear < 1) throw std::invalid_argument("Year cannot be less than 1.");
    year = newYear;
}

// setter for month with validation to ensure it is between 1 and 12
void Date::setMonth(short int newMonth) {
    if (newMonth < 1 || newMonth > 12) throw std::invalid_argument("Month must be between 1 and 12.");
    month = newMonth;
}

// setter for day with validation to ensure it is valid for the given month and year
void Date::setDay(short int newDay) {
    // array of days in each month
    static const short int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    short int maxDays = daysInMonth[month - 1];

    // adjust for leap years if the month is February
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) maxDays = 29;

    // validate the day for the given month and year
    if (newDay < 1 || newDay > maxDays) throw std::invalid_argument("Invalid day for the given month.");
    day = newDay;
}

// getter for year
short int Date::getYear() const { return year; }

// getter for month
short int Date::getMonth() const { return month; }

// getter for day
short int Date::getDay() const { return day; }

// utility function to validate the date
bool Date::isValidDate() const {
    // array of days in each month
    static const short int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    short int maxDays = daysInMonth[month - 1];

    // adjust for leap years if the month is February
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) maxDays = 29;

    // validate the month and day
    return month >= 1 && month <= 12 && day >= 1 && day <= maxDays;
}

// equality operator: checks if two dates are equal
bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

// stream insertion operator: formats the date as MM/DD/YYYY
std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << (date.month < 10 ? "0" : "") << date.month << "/"
       << (date.day < 10 ? "0" : "") << date.day << "/"
       << date.year;
    return os;
}
