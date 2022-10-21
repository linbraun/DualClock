#include "Clock.h"

Clock::Clock(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s; 
}

// Setters
void Clock::setSecond(int s) {
    second = s;
}
void Clock::setMinute(int m) {
    minute = m;
}
void Clock::setHour(int h) {
    hour = h;
}

// Getters
int Clock::getSecond() {
    return second;
}
int Clock::getMinute() {
    return minute;
}
int Clock::getHour() {
    return hour;
}