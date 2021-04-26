/**
 *  @file date.h
 *  @brief handle the data according the date
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <QString>

using namespace std;

///@param date class
class date
{
    int month;
    int day;
    int year;
    QString CompleteDate;

public:
    /// @brief Default constructor
    date();
    /// @brief Default constructor
    /// @param newMonth
    /// @param newDay
    /// @param newYear
    date(int newMonth, int newDay, int newYear);
    ///@brief Destructor
    ~date();

    ///@brief Accesors
    void setCompleteDate(QString newDate);
    void setMonth(int newMonth);
    void setDay(int newDay);
    void setYear(int newYear);


    ///@brief Mutators
    QString getCompleteDate(QString completeDate, int day, int month, int year);
    int getMonth();
    int getDay();
    int getYear();

};

#endif // DATE_H
