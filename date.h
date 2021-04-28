/**
 *  @file date.h
 *  @brief handle the data according the date
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <QDateTimeEdit>

using namespace std;

///@param date class
class Date
{
public:
    Date();
    Date(int newMonth, int newDay, int newYear);
    ~Date();

    int getMonth() const;
    int getDay() const;
    int getYear() const;

    void setMonth(int newMonth);
    void setDay(int newDay);
    void setYear(int newYear);

private:
    int day;
    int month;
    int year;
};

#endif // DATE_H
