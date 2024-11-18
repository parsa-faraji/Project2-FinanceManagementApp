#include "Time.hpp"
#include <stdexcept>

// default constructor
Time::Time() : hour(0), minute(0) {}

// parameterized constructor
Time::Time(short int hour, short int minute) : hour(hour), minute(minute) {
    if (!isValidTime()) {
        throw std::invalid_argument("Invalid time provided.");
    }
}

void Time::setHour(short int newHour) {
    if (newHour < 0 || newHour > 23) {
        throw std::invalid_argument("Hour must be between 0 and 23.");
    }
    hour = newHour;
}

void Time::setMinute(short int newMinute) {
    if (newMinute < 0 || newMinute > 59) {
        throw std::invalid_argument("Minute must be between 0 and 59.");
    }
    minute = newMinute;
}

short int Time::getHour() const { return hour; }
short int Time::getMinute() const { return minute; }

bool Time::isValidTime() const {
    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}

// opeartor overload

bool Time::operator==(const Time& other) const {
    return hour == other.hour && minute == other.minute;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << (time.hour < 10 ? "0" : "") << time.hour << ":"
       << (time.minute < 10 ? "0" : "") << time.minute;
    return os;
}
