#include "date.h"

date::date()
{
    month = 1;
    day = 1;
    year = 2000;
}
date::date(int newMonth, int newDay, int newYear){
    month = newMonth;
    day = newDay;
    year = newYear;
}
void date::setMonth(int newMonth)
{
    month = newMonth;
}
void date::setDay(int newDay)
{
    day = newDay;
}
void date::setYear(int newYear)
{
    year = newYear;
}



int date::getMonth()
{
    return month;
}
int date::getDay()
{
    return day;
}
int date::getYear()
{
    return year;
}

