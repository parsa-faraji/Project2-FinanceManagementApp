#ifndef Date_hpp
#define Date_hpp

#include <iostream>

struct Date {
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

    // utility function
    bool isValidDate() const;

    // equality operator
    bool operator==(const Date& other) const;

    // stream overload
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

#endif /* Date_hpp */
