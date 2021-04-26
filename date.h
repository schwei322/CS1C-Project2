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
class date
{

public:
    PurchaseData queryWithDate(QDate date);

};

#endif // DATE_H
