#include "database_manager.h"

/****************************************************************************//**
 *      Constructor
 *____________________________________________________________________________
 *
 *******************************************************************************/

Database_manager::Database_manager()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("bulk_club_database.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
}
/********************************************************************************/



/****************************************************************************//**
 *      Deconstructor
 *____________________________________________________________________________
 *
 *******************************************************************************/

Database_manager::~Database_manager()
{
    database.close();
}/*******************************************************************************/



/****************************************************************************//**
 *      get_member
 * ____________________________________________________________________________
 * Method queries Bulk Club database and retrieves all data of a member in the
 * form of a QStringList. Method uses membership_number to find member.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

QStringList Database_manager::get_memberInfo(QString membership_number) const
{
    QSqlQuery query;
    QStringList membersData;
    QString command = "SELECT Name, MembershipNumber, Type, ExpirationDate FROM Membership WHERE MembershipNumber IN(" + membership_number +")";
    if (query.exec(command))
    {
        while (query.next())
        {
            for (int i = 0; i < 4; i++)
            {
                membersData.append( query.value(i).toString() );
            }
        }
    }
    else
    {
        qDebug() << "Error = " << database.lastError();
    }
    return membersData;
}
/*******************************************************************************/



/****************************************************************************//**
 *      get_purchase
 * ____________________________________________________________________________
 * Method returns a vector of QStringLists. A vector element represents an purchse
 * made by a member. The element is a QStringList holding data about the purchase.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return purchases : Purchases made by member. Vector of QStrings where a vector
 *              element represents a purchacemade by the member and the QStringList is the
 *              purchace info.
*******************************************************************************/

QVector<QStringList> Database_manager::get_memberPurchases(QString membership_number) const
{
    QSqlQuery query;
    QStringList purchaseData;
    QVector<QStringList> purchases;
    QString sql_command;
    int columnNum;
    int numof_purchases_made_by_member;

    // Find out how many purchases made by member.

    // First, find out number of purchases made by member.
    sql_command = "SELECT COUNT(MembershipNumber) FROM Purchase WHERE MembershipNumber='" + membership_number +"';";
    query.prepare(sql_command);
    if( !query.exec())
    {
        qDebug() << "Error = " << database.lastError();
    }
    query.first();
    numof_purchases_made_by_member = query.value(0).toInt();
    sql_command.clear();

    // Find out number of columns in Purchse table
    query.prepare("SELECT * FROM Purchase");
    if (!query.exec())
    {
        qDebug() << "Error = " << database.lastError();
    }
    columnNum = query.record().count();

    // Resize vector
    purchases.resize(numof_purchases_made_by_member);

    sql_command = "SELECT Date, MembershipNumber, Product, Price, Quantity FROM Purchase WHERE MembershipNumber IN(" + membership_number +")";
    // Get QStringList of all purchases
    if (query.exec(sql_command))
    {
        while (query.next())
        {
            for (int i = 0; i < columnNum; i++)
            {
                purchaseData.append( query.value(i).toString() );
            }
        }
    }
    else
    {
        qDebug() << "Error = " << database.lastError();
    }

    // Split QStringList into multiple QStringLists;
    // Each individual QStringList is stored in vector.
    for (int i = 0; i < numof_purchases_made_by_member; i++)
    {
        for (int j = 0; j < columnNum; j++)
        {
            purchases[i].append(purchaseData[j]);
        }
    }

    return purchases;
}
/*******************************************************************************/



/****************************************************************************//**
 *      get_itemInfo
 * ____________________________________________________________________________
 * Method returns a vector of QStringLists. A vector element represents an
 * item. The element is a QStringList holding data about the purchase.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

QStringList Database_manager::get_itemInfo(QString item_name) const
{
    QSqlQuery query;
    QStringList item_data_list;
    QString command = "SELECT Name, Price FROM Items WHERE Name='" + item_name +"'";

    if (query.exec(command))
    {
        while (query.next())
        {
            for (int i = 0; i < 2; i++)
            {
                item_data_list.append( query.value(i).toString() );
            }
        }
    }
    else
    {
        qDebug() << "Error = " << database.lastError();
    }

    return item_data_list;
}
/*******************************************************************************/



/****************************************************************************//**
 *      ~~~~~~~
 * ____________________________________________________________________________
 * ___Description___
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/


/*******************************************************************************/
