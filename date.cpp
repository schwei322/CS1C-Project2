#include "date.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVector>
#include<iostream>
#include "database_initializer.h"
#include "purchasedata.h"

date::date(Database_initializer database_initializer)
{
    database_initializer.getDatabase(database);
}

QVector<PurchaseData> date::queryPurchasesByDay(QDate date)
{
    string str = "SELECT Date, MembershipNumber, Product, Price, Quantity FROM Purchase WHERE Date =" + to_string(date.month()) + "/" + to_string(date.day()) + "/" + to_string(date.year()) + ")";
    return issueQuery(str.c_str());
}

QVector<PurchaseData> date::queryPurchasesByDayAndMembershipType(QDate date, bool executiveMembership)
{
    string dateCondition = "Purchase.Date =" + to_string(date.month()) + "/" + to_string(date.day()) + "/" + to_string(date.year());
    string executive = executiveMembership ? "Executive" : "Regular";
    string membershipTypeCondition = "Membership.Type =" + executive;
    string fullCondition = dateCondition + " AND " + membershipTypeCondition;
    string join = "(Purchase JOIN Membership ON Purchase.MembershipNumber = Membership.MembershipNumber)";
    string str = "SELECT Purchase.Date, Purchase.MembershipNumber, Purchase.Product, Purchase.Price, Purchase.Quantity FROM " + join + " WHERE " + fullCondition + ")";
    return issueQuery(str.c_str());
}

QVector<PurchaseData> date::issueQuery(QString command)
{
    QVector<PurchaseData> result;
    QSqlQuery query;
    query.prepare(command);
    if(query.exec())
    {
        result = aggregateData(query);
    }
    else
    {
        qDebug() << "Error(" << __FUNCTION__ << ") = " << database.lastError();
    }
    return result;
}

QVector<PurchaseData> date::aggregateData(QSqlQuery query)
{
    QVector<PurchaseData> result;
    int columnNum = query.record().count();
    while(query.next())
    {
        int i;
        PurchaseData purchaseData;
        for(i = 0; i < columnNum; i++)
        {
            switch(i)
            {
            case 0: // Date value
                purchaseData.setDate(query.value(i).toString());
                break;
            case 1: // MembershipNumber
                purchaseData.setMembershipNumber(query.value(i).toInt());
                break;
            case 2: // Product
                purchaseData.setProduct(query.value(i).toString());
                break;
            case 3: // Price (TODO: do we have to go through toString().toFloat() or can we just call toInt directly?)
                purchaseData.setPrice(query.value(i).toString().toFloat());
                break;
            case 4: // Quantity (TODO: do we have to go through toString().toInt() or can we just call toInt directly?)
                purchaseData.setQuantity(query.value(i).toString().toInt());
                break;
            default:
                qDebug() << "invalid column number : " << i;
                break;
            }
        }
        result.append(purchaseData);
    }
    return result;
}

