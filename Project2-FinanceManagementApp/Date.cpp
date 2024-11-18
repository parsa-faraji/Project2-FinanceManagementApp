#include "Date.hpp"
#include <stdexcept>

Date::Date() : year(0), month(0), day(0) {}

Date::Date(short int year, short int month, short int day)
    : year(year), month(month), day(day) {}

void Date::setYear(short int newYear) {
    if (newYear < 1) throw std::invalid_argument("Year cannot be less than 1.");
    year = newYear;
}

void Date::setMonth(short int newMonth) {
    if (newMonth < 1 || newMonth > 12) throw std::invalid_argument("Month must be between 1 and 12.");
    month = newMonth;
}

void Date::setDay(short int newDay) {
    static const short int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    short int maxDays = daysInMonth[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) maxDays = 29;

    if (newDay < 1 || newDay > maxDays) throw std::invalid_argument("Invalid day for the given month.");
    day = newDay;
}

short int Date::getYear() const { return year; }
short int Date::getMonth() const { return month; }
short int Date::getDay() const { return day; }

bool Date::isValidDate() const {
    static const short int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    short int maxDays = daysInMonth[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) maxDays = 29;

    return month >= 1 && month <= 12 && day >= 1 && day <= maxDays;
}

bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << (date.month < 10 ? "0" : "") << date.month << "/"
       << (date.day < 10 ? "0" : "") << date.day << "/"
       << date.year;
    return os;
}
