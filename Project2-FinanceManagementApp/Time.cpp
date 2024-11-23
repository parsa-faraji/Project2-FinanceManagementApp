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
    if (newHour < 0 || newHour > 12) {
        throw std::invalid_argument("Hour must be between 0 and 12.");
    }
    hour = newHour;
}

void Time::setMinute(short int newMinute) {
    if (newMinute < 0 || newMinute > 59) {
        throw std::invalid_argument("Minute must be between 0 and 59.");
    }
    minute = newMinute;
}

void Time::setDayOrNight(string newDayOrNight) {
    if (dayOrNight != "pm" && dayOrNight != "am") {
        throw std::invalid_argument("Please pass am or pm in lowercase for day or night.");
    }
    dayOrNight = newDayOrNight;
}

short int Time::getHour() const { return hour; }
short int Time::getMinute() const { return minute; }
string Time::getDayOrNight() const { return dayOrNight;}

bool Time::isValidTime() const {
    return hour >= 0 && hour <= 12 && minute >= 0 && minute <= 59 && (dayOrNight == "pm" || dayOrNight == "am");
}

// opeartor overload

bool Time::operator==(const Time& other) const {
    return hour == other.hour && minute == other.minute && dayOrNight == other.dayOrNight;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << (time.hour < 10 ? "0" : "") << time.hour << ":"
       << (time.minute < 10 ? "0" : "") << time.minute << " " << time.dayOrNight;
    return os;
}
