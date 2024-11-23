#ifndef Date_hpp
#define Date_hpp

#include <iostream>

// Date structure - used for recording and reporting date
struct Date {
    // attributes
    short int year;
    short int month;
    short int day;

    // constructors
    Date();
    Date(short int year, short int month, short int day);

    // setters
    void setYear(short int newYear);
    void setMonth(short int newMonth);
    void setDay(short int newDay);

    // getters
    short int getYear() const;
    short int getMonth() const;
    short int getDay() const;

    // utility function to check if a date is valid
    bool isValidDate() const;

    // equality operator
    bool operator==(const Date& other) const;

    // stream overload
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif /* Date_hpp */
