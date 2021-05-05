#include "date.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVector>
#include<iostream>
#include "purchasedata.h"

date::date()
{
    database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    database.setDatabaseName("bulk_club_database.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
}

date::~date()
{
    database.close();
}

QVector<PurchaseData> date::queryPurchasesByDay(QDate date)
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName("C:\\Users\\Dayana Pulido\\Documents\\Saddleback\\Spring 2021\\CS1C\\Project 1\\CS1C-Project2\\bulk_club_database.db");
        database.open();
    }
    string str = "SELECT date, membership_number, product, price, quantity FROM Purchase WHERE date = '" + to_string(date.month()) + "/" + to_string(date.day()) + "/" + to_string(date.year()) + "'";
    return issueQuery(str.c_str());
}

QVector<PurchaseData> date::queryPurchasesByDayAndMembershipType(QDate date, QString membershipType)
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName("C:\\Users\\Dayana Pulido\\Documents\\Saddleback\\Spring 2021\\CS1C\\Project 1\\CS1C-Project2\\bulk_club_database.db");
        database.open();
    }
    string dateCondition = "p.date = '" + to_string(date.month()) + "/" + to_string(date.day()) + "/" + to_string(date.year()) + "'";
    string membershipTypeCondition = "m.membership_type = '" + membershipType.toStdString() + "'";
    string fullCondition = dateCondition + " AND " + membershipTypeCondition;
    string join = "(Purchase as p JOIN Member as m ON p.membership_number = m.membership_number)";
    string str = "SELECT date, p.membership_number, p.product, p.price, p.quantity FROM " + join + " WHERE (" + fullCondition + ")";
    return issueQuery(str.c_str());
}

QVector<PurchaseData> date::issueQuery(QString command)
{
    QVector<PurchaseData> result;
    QSqlQuery query(database);
    query.prepare(command);
    qDebug() << command << "\n";
    if(query.exec())
    {
        result = aggregateData(query);
    }
    else
    {
        qDebug() << "Error(" << __FUNCTION__ << ") = " << database.lastError() << database.drivers();
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

