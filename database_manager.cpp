#include "database_manager.h"
#include <QVariant>
#include <QSqlField>
#include "member.h"

using namespace std;
/****************************************************************************//**
 *      Constructor
 *____________________________________________________________________________
 *
 *******************************************************************************/

DatabaseManager::DatabaseManager()
{
    database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");

    database.setDatabaseName(databasePath);

    qDebug() << databasePath << "      DATABASE P{ATHHHHHHHH";

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

DatabaseManager::~DatabaseManager()
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

QStringList DatabaseManager::get_memberInfo(QString membership_number) const
{
    QSqlQuery query(database);
    QStringList membersData;
    QString command = "SELECT name, membership_number, membership_type, expiration_date FROM Member WHERE membership_number IN(" + membership_number +")";
    int columnNum;

    // Find out number of columns in Membership table
    query.prepare("SELECT * FROM Member");
    if (!query.exec())
    {
        qDebug() << "Error = " << database.lastError();
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

QVector<QStringList> DatabaseManager::get_memberPurchases(QString membership_number) const
{
    QSqlQuery query(database);
    QStringList purchaseData;
    QVector<QStringList> purchases;
    QString sql_command;
    int columnNum;
    int numof_purchases_made_by_member;
    QStringList buff;

    // Find out how many purchases made by member.

    // First, find out number of purchases made by member.
    sql_command = "SELECT COUNT(membership_number) FROM Purchase WHERE membership_number='" + membership_number +"';";
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

    sql_command = "SELECT date, membership_number, product, price, quantity FROM Purchase WHERE membership_number IN(" + membership_number +")";
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

    /*
    qDebug() << "PurchaseData:\n" << purchaseData;
    qDebug() << "numof_purchases_made_by_member: " << numof_purchases_made_by_member;
    qDebug() << "column num: " << columnNum;
    qDebug() << "vector size: " << purchases.size();
    qDebug() << "\n\n\n";
    */

    // Assign every item's data to its own QStringList. All QStringLists are assigned to a QVector.
    int j = 0;
    buff.clear();
    for (int i = 0; i < purchaseData.size(); i++)
    {
        if(((i % columnNum == 0) && (i != 0 )))
        {
            purchases[j].append(buff);
            j++;
            buff.clear();
        }
        buff.append(purchaseData[i]);
    }
    purchases[j].append(buff);
    j++;
    buff.clear();

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

QStringList DatabaseManager::get_itemInfo(QString item_name) const
{
    QSqlQuery query(database);
    QStringList item_data_list;
    QString command = "SELECT item_name, item_price FROM Items WHERE item_name='" + item_name +"'";

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
 *      update_totalAmountSpent
 * ____________________________________________________________________________
 * ___Description___
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void DatabaseManager::update_totalAmountSpent(QString membership_number, QString total_amount_spent) const
{
    QSqlQuery query(database);
    QStringList membersData;
    QString sql_command = "UPDATE Member SET total_amount_spent='" + total_amount_spent +"' WHERE membership_number='" + membership_number + "'";

    if (!query.exec(sql_command))
    {

        qDebug() << "Error = " << database.lastError();

    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      update_totalAmountSpent
 * ____________________________________________________________________________
 * ___Description___
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void DatabaseManager::insert_row_in_inventory(QString item_name, QString num_of_items, QString sell_quantity, QString total_revenue) const
{
    QSqlQuery query(database);

    query.prepare("INSERT INTO Inventory (item_name, num_of_items, sell_quantity, total_revenue)"
                    "VALUES (:item_name, :num_of_items, :sell_quantity, :total_revenue)");
    query.bindValue(":item_name", item_name);
    query.bindValue(":num_of_items", num_of_items);
    query.bindValue(":sell_quantity", sell_quantity);
    query.bindValue(":total_revenue", total_revenue);

    if (!query.exec())
    {
        qDebug() << query.lastError();
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      delete_row_in_inventory
 * ____________________________________________________________________________
 * Deletes row in inventory given a name. NOTE: if inventory has
 * two or more rows with the same name, ALL OF THEM WILL BE DELETED!!!
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void DatabaseManager::delete_row_in_inventory(QString item_name) const
{
    QSqlQuery query(database);
    QString sql_command = "DELETE FROM Inventory WHERE item_name='" + item_name + "'";

    query.prepare(sql_command);
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }
}
/*******************************************************************************/


QString DatabaseManager::get_member_name_from_id(int id)
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(databasePath);
        database.open();
    }

    QString queryStr = "SELECT name FROM Member WHERE membership_number = '" + QString::number(id) + "'";

    QSqlQuery query(database);
    query.prepare(queryStr);

    QString name;

    if(query.exec())
    {
        while(query.next())
        {
            name = query.value(0).toString();
        }
    }
    else
    {
        qDebug() << "Error(" << __FUNCTION__ << ") = " << database.lastError() << database.drivers();
    }

    return name;
}

/* PurchaseData */

QVector<PurchaseData> DatabaseManager::issue_purchases_query(QString command)
{
    QVector<PurchaseData> result;
    QSqlQuery query(database);
    query.prepare(command);

    qDebug() << command << "\n";

    if(query.exec())
    {
        result = aggregate_purchases_data(query);
    }
    else
    {
        qDebug() << "Error(" << __FUNCTION__ << ") = " << database.lastError() << database.drivers();
    }

    return result;
}

QVector<Member*> DatabaseManager::aggregate_member_data(QSqlQuery query)
{
    QVector<Member*> result;

    int columnNum = query.record().count();

    while(query.next())
    {
        QString name;
        int membership_number;
        QString membership_type;
        QString membership_expiration_date;
        double total_amount_spent;
        double rebate_amount;

        for(int i = 0; i < columnNum; i++)
        {
            switch(i)
            {
            case 0: // name
                name = query.value(i).toString();
                qDebug() << "FOUND NAME HERE " << name << "\n";
                break;
            case 1: // membership_number
                membership_number = query.value(i).toInt();
                break;
            case 2: // membership_type
                membership_type = query.value(i).toString();
                break;
            case 3: // membership_expiration_date
                membership_expiration_date = query.value(i).toString();
                break;
            case 4: // total_amount_spent
                total_amount_spent = query.value(i).toDouble();
                break;
            case 5: // rebate amount
                rebate_amount = query.value(i).toDouble();
                break;
            default:
                qDebug() << "Invalid column number : " << i;
                break;
            }
        }
        Member* member = new Member(name, membership_number, membership_type, membership_expiration_date, total_amount_spent, rebate_amount);
        result.append(member);
    }

    return result;
}

QVector<PurchaseData> DatabaseManager::aggregate_purchases_data(QSqlQuery query)
{
    QVector<PurchaseData> result;

    int columnNum = query.record().count();

    while(query.next())
    {

        PurchaseData purchaseData;

        for(int i = 0; i < columnNum; i++)
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
                case 3: // Price
                    purchaseData.setPrice(query.value(i).toFloat());
                    break;
                case 4: // Quantity
                    purchaseData.setQuantity(query.value(i).toInt());
                    break;
                default:
                    qDebug() << "Invalid column number : " << i;
                    break;
            }
        }

        result.append(purchaseData);
    }

    return result;
}

QVector<PurchaseData> DatabaseManager::get_report_all_purchases()
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(databasePath);
        database.open();
    }

    QString str = "SELECT date, membership_number, product, price, quantity FROM Purchase";

    return issue_purchases_query(str);
}

QVector<PurchaseData> DatabaseManager::get_report_purchases_by_date(QDate date)
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(databasePath);
        database.open();
    }

    QString str = "SELECT date, membership_number, product, price, quantity FROM Purchase WHERE date = '" + QString::number(date.month()) + "/" + QString::number(date.day()) + "/" + QString::number(date.year()) + "'";

    return issue_purchases_query(str);
}

QVector<Member*> DatabaseManager::get_report_expired_memberships_from_month(uint month)
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(databasePath);
        database.open();
    }

    string normalized_month = to_string(month).length() == 1 ? "0" + to_string(month) : to_string(month);
    string str = "SELECT name, membership_number, membership_type, expiration_date, total_amount_spent, rebate_amount FROM MEMBER WHERE expiration_date LIKE '" + normalized_month + "/%'";
    QString qString = str.c_str();

    QVector<Member*> result;
    QSqlQuery query(database);
    query.prepare(qString);

    qDebug() << qString << "\n";

    if(query.exec())
    {
        result = aggregate_member_data(query);
    }
    else
    {
        qDebug() << "Error(" << __FUNCTION__ << ") = " << database.lastError() << database.drivers();
    }

    return result;
}
