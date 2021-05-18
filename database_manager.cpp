#include "database_manager.h"
#include <QVariant>
#include <QSqlField>
#include "member.h"

/****************************************************************************//**
 *      Constructor
 *____________________________________________________________________________
 *
 *******************************************************************************/

DatabaseManager::DatabaseManager()
{
    database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    database.setDatabaseName(databasePath);
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

void DatabaseManager::update_rebateAmount(QString membership_number, QString rebate_amount) const
{
    QSqlQuery query(database);
    QStringList membersData;
    QString sql_command = "UPDATE Member SET rebate_amount='" + rebate_amount +"' WHERE membership_number='" + membership_number + "'";

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

void DatabaseManager::add_item(QString item_name, QString item_price) const
{
    QSqlQuery query(database);
    QString sql_command = "INSERT INTO Items (item_name, item_price) VALUES('"+item_name+"','"+item_price+"')";

    query.prepare(sql_command);
    if(!query.exec())
    {
        qDebug() << query.lastError();
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

void DatabaseManager::delete_item(QString item_name) const
{
    QSqlQuery query(database);
    QString sql_command = "DELETE FROM Items WHERE item_name = '"+item_name+"'";

    query.prepare(sql_command);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
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

void DatabaseManager::update_item(QString item_name, QString item_price) const
{
    QSqlQuery query(database);
    QString sql_command1 = "UPDATE Items SET item_price = '"+item_price+"' WHERE item_name = '"+item_name+"'";
    QString sql_command2 = "UPDATE Purchase SET price = '"+item_price+"' WHERE product = '"+item_name+"'";

    query.prepare(sql_command1);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }

    query.prepare(sql_command2);
    if(!query.exec())
    {
        qDebug() << query.lastError();
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

bool DatabaseManager::check_item_existance(QString item_name) const
{
    QSqlQuery query(database);
    QString sql_command = "SELECT EXISTS(SELECT 1 FROM Items WHERE item_name='"+item_name+"')";

    QString item_exists;

    query.prepare(sql_command);
    if(query.exec(sql_command))
    {
        while (query.next())
        {
            item_exists.append( query.value(0).toString() );
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

bool DatabaseManager::check_item_existance(QString item_name, QString item_id) const
{
    QSqlQuery query(database);
    QString sql_command = "SELECT EXISTS(SELECT 1 FROM Items WHERE item_name='"+item_name+"' AND item_id='"+item_id+"')";

    QString item_exists;

    query.prepare(sql_command);
    if(query.exec(sql_command))
    {
        while (query.next())
        {
            item_exists.append( query.value(0).toString() );
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

void DatabaseManager::add_member(QString member_name, QString membership_type) const
{
    QSqlQuery query(database);
    QString sql_command = "INSERT INTO Member (name, membership_type, expiration_date) VALUES('"+member_name+"','"+membership_type+"', '05/17/2022')";

    query.prepare(sql_command);
    if(!query.exec())
    {
        qDebug() << query.lastError();
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

void DatabaseManager::delete_member(QString member_name, QString membership_id) const
{
    QSqlQuery query(database);
    QString sql_command = "DELETE FROM Member WHERE name='" + member_name + "' AND membership_number='"+membership_id+"'";

    query.prepare(sql_command);
    if(!query.exec())
    {
        qDebug() << query.lastError();
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

bool DatabaseManager::check_member_existance(QString membership_number) const
{
    QSqlQuery query(database);
    QString sql_command = "SELECT EXISTS(SELECT 1 FROM Member WHERE membership_number='"+membership_number+"')";

    QString item_exists;

    query.prepare(sql_command);
    if(query.exec(sql_command))
    {
        while (query.next())
        {
            item_exists.append( query.value(0).toString() );
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
 *      @param  member_name, membership_number) const
 *
 * \b OUTPUT:
 *      @return the item if it does exit
*******************************************************************************/

bool DatabaseManager::check_member_existance(QString member_name, QString membership_number) const
{
    QSqlQuery query(database);
    QString sql_command = "SELECT EXISTS(SELECT 1 FROM Member WHERE name='"+member_name+"' AND membership_number='"+membership_number+"')";

    QString item_exists;

    query.prepare(sql_command);
    if(query.exec(sql_command))
    {
        while (query.next())
        {
            item_exists.append( query.value(0).toString() );

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

void DatabaseManager::add_member_purchase(QString membership_number, QString product, QString price, QString quantity, QString date) const
{
    QSqlQuery query(database);
    QString sql_command = "INSERT INTO Purchase (membership_number, product, price, quantity, date) VALUES('"+membership_number+"','"+product+"','"+price+"','"+quantity+"','"+date+"')";

    // First check if member exists. Cannot add purchase to a non existant member
    if (check_member_existance(membership_number) == false)
    {
        qDebug() << "Purchase did not insert. Reason: Member does not exist.";
        return;
    }

    query.prepare(sql_command);
    if(query.exec(sql_command))
    {
        qDebug() << "Purchase Inserted Successful! [member_number: " << membership_number << " ]";

    }
    else
    {
        qDebug() << query.lastError();
    }
}
/*******************************************************************************/


/****************************************************************************//**
 *      issue_items_query
 * ____________________________________________________________________________
 * Method that creates a query to aggregate items to the database.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param command
 *
 * \b OUTPUT:
 *      @return result, aggregate items data
*******************************************************************************/

/* PurchaseData */


/****************************************************************************//**
 *      PurchaseData
 * ____________________________________________________________________________
 * Method returns issued items query.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param command : QString representing SQLite commmand.
 *
 * \b OUTPUT:
 *      @return result : QVector representing purchase data.
*******************************************************************************/


QVector<PurchaseData> DatabaseManager::issue_items_query(QString command)
{
    QVector<PurchaseData> result;
    QSqlQuery query(database);
    query.prepare(command);

    qDebug() << command << "\n";

    if(query.exec())
    {
        result = aggregate_items_data(query);
    }
    else
    {
        qDebug() << "Error(" << __FUNCTION__ << ") = " << database.lastError() << database.drivers();
    }

    return result;
}

/****************************************************************************//**
 *      issue_purchases_query
 * ____________________________________________________________________________
 * Method that issues a query according the users election
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param command
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

/*******************************************************************************/



/****************************************************************************//**
 *      issue_purchases_query
 * ____________________________________________________________________________
 * Method queries purchases. Returns a QVector containing purchase data.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param command : QString representing SQLite commmand.
 *
 * \b OUTPUT:
 *      @return result : QVector representing purchase data.
*******************************************************************************/


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

/****************************************************************************//**
 *      aggregate_items_data
 * ____________________________________________________________________________
 * Method that traverse the database counting and adding data
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param QSqlQuery query
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

/*******************************************************************************/



/****************************************************************************//**
 *      aggregate_items_data
 * ____________________________________________________________________________
 * Method aggregates a set of items data.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param query : SqlQuery instance needed to query the Bulk Club database.
 *
 * \b OUTPUT:
 *      @return result : QVector representing purchase data.
*******************************************************************************/

QVector<PurchaseData> DatabaseManager::aggregate_items_data(QSqlQuery query)
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
                case 0: // Product
                    purchaseData.setProduct(query.value(i).toString());
                    break;
                case 1: // Price
                    purchaseData.setPrice(query.value(i).toFloat());
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

/****************************************************************************//**
 *      aggregate_purchases_data
 * ____________________________________________________________________________
 * Method that traverse the database counting and adding purchases data
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param QSqlQuery query
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

/*******************************************************************************/



/****************************************************************************//**
 *      aggregate_purchases_data
 * ____________________________________________________________________________
 * Method aggregates purchase data from database.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param query : SqlQuery instance needed to query the Bulk Club database.
 *
 * \b OUTPUT:
 *      @return result : QVector representing purchase data.
*******************************************************************************/


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

/****************************************************************************//**
 *      aggregate_purchases_data
 * ____________________________________________________________________________
 * Method that traverse the database counting and adding purchases data
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param QSqlQuery query
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

/*******************************************************************************/



/****************************************************************************//**
 *      aggregate_member_data
 * ____________________________________________________________________________
 * Method aggregates member data from Bulk Club database.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param query : SqlQuery instance needed to query the Bulk Club database.
 *
 * \b OUTPUT:
 *      @return result : QVector representing purchase data.
*******************************************************************************/


QVector<Member> DatabaseManager::aggregate_member_data(QSqlQuery query)
{
    QVector<Member> result;

    int columnNum = query.record().count();

    while(query.next())
    {
        Member member;

        for(int i = 0; i < columnNum; i++)
        {
            switch(i)
            {
                case 0: // name
                    member.set_name(query.value(i).toString());
                    break;
                case 1: // membership_number
                    member.set_membership_number(query.value(i).toInt());
                    break;
                case 2: // membership_type
                    member.set_membership_type(query.value(i).toString());
                    break;
                case 3: // membership_expiration_date
                    member.set_membership_expiration_date(query.value(i).toString());
                    break;
                case 4: // total_amount_spent
                    member.set_total_amount_spent(query.value(i).toFloat());
                    break;
                case 5: // rebate amount
                    member.set_rebate_amount(query.value(i).toFloat());
                    break;
                default:
                    qDebug() << "Invalid column number : " << i;
                    break;
            }
        }

        result.append(member);
    }

    return result;
}

/****************************************************************************//**
 *      get_report_all_items
 * ____________________________________________________________________________
 * Method that traverse the database finding all the items in the data bes
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param QSqlQuery query
 *
 * \b OUTPUT:
 *      @return The items in the data base
*******************************************************************************/

/*******************************************************************************/



/****************************************************************************//**
 *      get_report_all_items
 * ____________________________________________________________________________
 * Method gets report for all items.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return issue_items_query(str) : QVector
*******************************************************************************/

QVector<PurchaseData> DatabaseManager::get_report_all_items()
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(databasePath);
        database.open();
    }

    QString str = "SELECT item_name, item_price FROM Items";

    return issue_items_query(str);
}

/****************************************************************************//**
 *      get_report_all_purchases
 * ____________________________________________________________________________
 * Method that traverse the database finding all the purchases in the database
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param QSqlQuery query
 *
 * \b OUTPUT:
 *      @return all the purchases in the data base
*******************************************************************************/

/*******************************************************************************/



/****************************************************************************//**
 *      get_report_all_purchases
 * ____________________________________________________________________________
 * Method gets all purchases.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return issue_purchases_query(str) : QVector containing purchase information.
*******************************************************************************/

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

/****************************************************************************//**
 *      get_report_purchases_by_date
 * ____________________________________________________________________________
 * Method that traverse the database finding and sorting the purchases made by
 * any selected day
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param QDate date
 *
 * \b OUTPUT:
 *      @return the purchases of the selected day
*******************************************************************************/

/*******************************************************************************/



/****************************************************************************//**
 *      get_report_purchases_by_date
 * ____________________________________________________________________________
 * Method gets purchases sorted by date.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param date : QDate representing date
 *
 * \b OUTPUT:
 *      @return issue_purchases_query(str) : QVector
*******************************************************************************/

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

/****************************************************************************//**
 *      get_report_expired_memberships_by_month
 * ____________________________________________________________________________
 * Method that traverse the database finding and sorting the members who their
 * membership expires the selected month
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param int month
 *
 * \b OUTPUT:
 *      @return member who`s membershyp expires the selected month
*******************************************************************************/

/*******************************************************************************/



/****************************************************************************//**
 *      get_report_expired_memberships_by_month
 * ____________________________________________________________________________
 * Method gets expired memberships by month.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param month : integer representing month.
 *
 * \b OUTPUT:
 *      @return result : QVector representing purchase data.
*******************************************************************************/


QVector<Member> DatabaseManager::get_report_expired_memberships_by_month(int month)
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(databasePath);
        database.open();
    }

    QString normalized_month = QString::number(month).length() == 1 ? "0" + QString::number(month) : QString::number(month);
    QString str = "SELECT name, membership_number, membership_type, expiration_date, total_amount_spent, rebate_amount FROM member WHERE expiration_date LIKE '" + normalized_month + "/%'";

    QVector<Member> result;
    QSqlQuery query(database);
    query.prepare(str);

    qDebug() << str << "\n";

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
/****************************************************************************//**
 *      get_report_all_purchases_per_member()
 * ____________________________________________________________________________
 * Method that traverse the database finding and sorting all the purchases
 * made by a member
/*******************************************************************************/



/****************************************************************************//**
 *      get_report_all_purchases_per_member
 * ____________________________________________________________________________
 * Method gets all purchases per member
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return all purchases by member
*******************************************************************************/

QVector<MemberPurchaseData> DatabaseManager::get_report_all_purchases_per_member()
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
        database.setDatabaseName(databasePath);
        database.open();
    }

    QString str = "SELECT Member.name, Member.membership_number, Member.membership_type, Member.expiration_date, Member.total_amount_spent, Member.rebate_amount, Purchase.price, Purchase.quantity FROM Member LEFT JOIN Purchase ON Member.membership_number = Purchase.membership_number ORDER BY Member.membership_number";

    QVector<MemberPurchaseData> result;

    QSqlQuery query(database);
    query.prepare(str);

    qDebug() << str << "\n";

    if(query.exec())
    {
        int columnNum = query.record().count();

        while(query.next())
        {

            MemberPurchaseData purchaseData;

            for(int i = 0; i < columnNum; i++)
            {
                switch(i)
                {
                    case 0: // Name
                        purchaseData.setName(query.value(i).toString());
                        break;
                    case 1: // MembershipNumber
                        purchaseData.setMembershipNumber(query.value(i).toInt());
                        break;
                    case 2: // MembershipType
                        purchaseData.setMembershipType(query.value(i).toString());
                        break;
                    case 3: // ExpirationDate
                        purchaseData.setExpirationDate(query.value(i).toString());
                        break;
                    case 4: // TotalSpent
                        purchaseData.setTotalSpent(query.value(i).toFloat());
                        break;
                    case 5: // RebateAmount
                        purchaseData.setRebateAmount(query.value(i).toFloat());
                        break;
                    case 6: // Price
                        purchaseData.setPrice(query.value(i).toFloat());
                        break;
                    case 7: // Quantity
                        purchaseData.setQuantity(query.value(i).toInt());
                        break;
                    default:
                        qDebug() << "Invalid column number : " << i;
                        break;
                }
            }

            result.append(purchaseData);
        }
    }
    else
    {
        qDebug() << "Error(" << __FUNCTION__ << ") = " << database.lastError() << database.drivers();
    }

    return result;
}
/*******************************************************************************/

