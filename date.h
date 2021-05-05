/*
 *  @file date.h
 *  @brief handle the data according the date
 *   */

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <QDateTimeEdit>
#include <QString>
#include <member.h>
#include <QtSql/QSqlDatabase>
#include "purchasedata.h"

using namespace std;
class date
{
public:
    date();
    ~date();
    // 1 ONLY FOCUS ON THIS FOR NOW
    QVector<PurchaseData> queryPurchasesByDay(QDate date);
    // 2 ONLY FOCUS ON THIS FOR NOW
    QVector<PurchaseData> queryPurchasesByDayAndMembershipType(QDate date, QString membershipType);

    /*// 3

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
   MemberData *getMemberById(int id);*/

private:
    QSqlDatabase database;
    QVector<PurchaseData> aggregateData(QSqlQuery query);
    QVector<PurchaseData> issueQuery(QString command);
};

#endif // DATE_H
