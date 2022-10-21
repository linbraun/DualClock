#pragma once
class Clock
{
private:
    int second;
    int minute;
    int hour;

public:
    Clock(int h, int m, int s);
    void setSecond(int s);
    void setMinute(int m);
    void setHour(int h);
    int getSecond();
    int getMinute();
    int getHour();
};
