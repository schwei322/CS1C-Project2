#include "date.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVector>

date::date()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("bulk_club_database.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
}

QVector<PurchaseData> date::queryByDay(QDate date)
{
    QVector<PurchaseData> result;
    QSqlQuery query;
    QStringList purchaseData;
    QString command = "SELECT Date, MembershipNumber, Product, Price, Quantity FROM Purchase WHERE Date =" + membership_number +")";
    int columnNum;

    // Find out number of columns in Membership table
    query.prepare(command);
    if(query.exec())
    {
        while(query.next())
        {

        }
    }
    else
    {
        qDebug() << "Error = " << database.lastError();
    }
    if (!query.exec())
    {

    }
    columnNum = query.record().count();

    if (query.exec(command))
    {
        while (query.next())
        {
            for (int i = 0; i < columnNum; i++)
            {
                membersData.append( query.value(i).toString() );
            }
        }
    }
    else
    {
        qDebug() << "Error = " << database.lastError();
    }
    return result;
}

PurchaseData * date::queryByDayAndMembershipType(QDate date, bool executiveMembership)
{

}

