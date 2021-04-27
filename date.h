/**
 *  @file date.h
 *  @brief handle the data according the date
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <QDateTimeEdit>
#include <QString>

using namespace std;
class date
{

public:
    // 1
    PurchaseData *queryPurchasesByDay(QDate date);
    // 2
    PurchaseData *queryPurchasesByDayAndMembershipType(QDate date, bool executiveMembership);

    // 3
    MemberData *getPurchaseDataOfMembers();

    // 4
    PurchaseData *getAllPurchases();

    // 6
    MemberData *getExpiredMembersByMonth(int month);

    // 7
    void deleteMember(int customerId);

    // 8
    void addNewPurchase(PurchaseData purchaseData);

    // 9
    void deleteItem(ItemData item);

    // 9
    void changeItemPrice(int price);

    // 10
    PurchaseData *queryPurchasesByItemName(QString string);

    // 11, 12, 13
    MemberData *getMemberById(int id);

};

#endif // DATE_H
