#ifndef Time_hpp
#define Time_hpp

#include <iostream>

struct Time {
    short int hour;    // 0 to 23
    short int minute;  // 0 to 59

    // constructors
    Time();
    Time(short int hour, short int minute);

    // setters
    void setHour(short int newHour);
    void setMinute(short int newMinute);

    // getters
    short int getHour() const;
    short int getMinute() const;

    // utility function
    bool isValidTime() const;

    // equality operator
    bool operator==(const Time& other) const;

    // stream overload
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

#endif /* Time_hpp */
