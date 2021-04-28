#include "date.h"

Date::Date()
{
    month = 1;
    day = 1;
    year = 2000;
}

Date::Date(int newMonth, int newDay, int newYear)
{
    month = newMonth;
    day = newDay;
    year = newYear;
}

Date::~Date()
{

}

int Date::getMonth() const
{
    return month;
}
int Date::getDay() const
{
    return day;
}
int Date::getYear() const
{
    return year;
}

void Date::setMonth(int newMonth)
{
    month = newMonth;
}
void Date::setDay(int newDay)
{
    day = newDay;
}
void Date::setYear(int newYear)
{
    year = newYear;
}
