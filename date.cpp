#include "date.h"

PurchaseData * date::queryByDay(QDate date)
{
   // select (customer_id, item, price, quantity
}

PurchaseData * date::queryByDayAndMembershipType(QDate date, bool executiveMembership)
{

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
