#include "database_manager.h"
#include <QVariant>
#include <QSqlField>

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
    else
    {
        // qDebug() << "Success: Database connected to database when Database_manager obj created.";
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
 *      add_member
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void Database_manager::add_member(QString member_name, QString membership_type) const
{
    QSqlQuery sql_query;

    if(!sql_query.exec("INSERT INTO Member (name, membership_type) VALUES('"+member_name+"','"+membership_type+"')"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Inserted Successful!";
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      delete_member
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void Database_manager::delete_member(QString member_name, QString membership_id) const
{
    QSqlQuery query;
    QString sql_command = "DELETE FROM Member WHERE name='" + member_name + "' AND membership_number='"+membership_id+"'";
    query.prepare(sql_command);
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }
    else
    {
        qDebug() << "Member "+member_name+" (ID# "+membership_id+") deleted sucessfully.\n";
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      check_member_existance
 * ____________________________________________________________________________
 * Method checks if member exists by using corresponding arguements. Returns
 * true if member exists; otherwise method returns false.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

bool Database_manager::check_member_existance(QString membership_number) const
{
    QString command = "SELECT EXISTS(SELECT 1 FROM Member WHERE membership_number='"+membership_number+"')";
    QSqlQuery sql_query;
    QString item_exists;

    if(sql_query.exec(command))
    {
        while (sql_query.next())
        {
            item_exists.append( sql_query.value(0).toString() );
        }
    }
    else
    {
        qDebug() << "Check NOT successful!";
    }

    return item_exists.toInt();
}
/*******************************************************************************/



/****************************************************************************//**
 *      check_member_existance
 * ____________________________________________________________________________
 * Method checks if member exists of corresponding arguements exists. Returns
 * true if member exists; otherwise method returns false.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

bool Database_manager::check_member_existance(QString member_name, QString membership_number) const
{
    QString command = "SELECT EXISTS(SELECT 1 FROM Member WHERE name='"+member_name+"' AND membership_number='"+membership_number+"')";
    QSqlQuery sql_query;
    QString item_exists;

    if(sql_query.exec(command))
    {
        while (sql_query.next())
        {
            item_exists.append( sql_query.value(0).toString() );
        }
    }
    else
    {
        qDebug() << "Check NOT successful!";
    }

    return item_exists.toInt();
}
/*******************************************************************************/



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
 *      add_member_purchase
 * ____________________________________________________________________________
 * Method adds a purchase for a specific member. Purchase is tied to member's
 * id (member_number).
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void Database_manager::add_member_purchase(QString membership_number, QString product, QString price, QString quantity, QString date) const
{
    QSqlQuery sql_query;
    QString sql_command;
    sql_command = "INSERT INTO Purchase (membership_number, product, price, quantity, date) VALUES('"+membership_number+"','"+product+"','"+price+"','"+quantity+"','"+date+"')";

    // First check if member exists. Cannot add purchase to a non existant member
    if (check_member_existance(membership_number) == false)
    {
        qDebug() << "Purchase did not insert. Reason: Member does not exist.";
        return;
    }

    if(!sql_query.exec(sql_command))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Purchase Inserted Successful! [member_number: " << membership_number << " ]";
    }
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

QStringList Database_manager::get_itemInfo(QString item_name) const
{
    QSqlQuery query;
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

void Database_manager::update_totalAmountSpent(QString membership_number, QString total_amount_spent) const
{
    QSqlQuery query;
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

void Database_manager::insert_row_in_inventory(QString item_name, QString num_of_items, QString sell_quantity, QString total_revenue) const
{
    QSqlQuery query;

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

void Database_manager::delete_row_in_inventory(QString item_name) const
{
    QSqlQuery query;
    QString sql_command = "DELETE FROM Inventory WHERE item_name='" + item_name + "'";

    query.prepare(sql_command);
    if (!query.exec())
    {
        qDebug() << query.lastError();
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      add_item
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void Database_manager::add_item(QString item_name, QString item_price) const
{
    QSqlQuery sql_query;

    if(!sql_query.exec("INSERT INTO Items (item_name, item_price) VALUES('"+item_name+"','"+item_price+"')"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Inserted Successful!";
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      delete_item
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void Database_manager::delete_item(QString item_name, QString item_id)
{
    QSqlQuery sql_query;

    if(!sql_query.exec("DELETE FROM Items WHERE item_name = '"+item_name+"' and item_id = '"+item_id+"'"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Delete Successful!";
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      check_item_existance
 * ____________________________________________________________________________
 * Checks if item exists in database. Returns true if item already exists.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param item_name
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

bool Database_manager::check_item_existance(QString item_name)
{
    QString command = "SELECT EXISTS(SELECT 1 FROM Items WHERE item_name='"+item_name+"')";
    QSqlQuery sql_query;
    QString item_exists;

    if(sql_query.exec(command))
    {
        while (sql_query.next())
        {
            item_exists.append( sql_query.value(0).toString() );
        }
    }
    else
    {
        qDebug() << "Check NOT successful!";
    }

    return item_exists.toInt();

}
/*******************************************************************************/



/****************************************************************************//**
 *      check_item_existance
 * ____________________________________________________________________________
 * Checks if item exists in database. Returns true if item already exists.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param item_name
 *      @param item_id
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

bool Database_manager::check_item_existance(QString item_name, QString item_id)
{
    QString command = "SELECT EXISTS(SELECT 1 FROM Items WHERE item_name='"+item_name+"' AND item_id='"+item_id+"')";
    QSqlQuery sql_query;
    QString item_exists;

    if(sql_query.exec(command))
    {
        while (sql_query.next())
        {
            item_exists.append( sql_query.value(0).toString() );
        }
    }
    else
    {
        qDebug() << "Check NOT successful!";
    }

    return item_exists.toInt();
}
/*******************************************************************************/



/****************************************************************************//**
 *      update_item
 * ____________________________________________________________________________
 * Checks if item exists in database. Returns true if item already exists.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void Database_manager::update_item(QString item_name, QString item_price)
{

    QSqlQuery sql_query;

    //SQLite command if you want to include item_id
    //if(!sql_query.exec("UPDATE Items SET Price = '"+item_price+"' WHERE Name = '"+item_name+"' AND item_id='"+item_id+"'"))
    if(!sql_query.exec("UPDATE Items SET item_price = '"+item_price+"' WHERE item_name = '"+item_name+"'"))

    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Update Successful!";
    }
}
/*******************************************************************************/






