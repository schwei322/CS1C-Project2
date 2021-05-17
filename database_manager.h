/**
 *  @file database_manager.h
 *  @brief Handles and creates queries to get data from the data base
*/
#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QDateTimeEdit>
#include <QProcessEnvironment>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtDebug>
#include <QVector>
#include "member.h"

#include "purchasedata.h"

///@brief path that connects to the database
const QString databasePath = QProcessEnvironment::systemEnvironment().value("DBPATH");

/// Class instance connects to Bulk Club's database.
///
/// Has methods that can change database fields.
class DatabaseManager
{
private:
    /**
     * @brief database queries
     */
    QSqlDatabase database;
    QVector<PurchaseData> issue_items_query(QString command);
    QVector<PurchaseData> issue_purchases_query(QString command);
    QVector<PurchaseData> aggregate_items_data(QSqlQuery query);
    QVector<PurchaseData> aggregate_purchases_data(QSqlQuery query);
    QVector<Member> aggregate_member_data(QSqlQuery query);

public:
    DatabaseManager();
    ~DatabaseManager();

    /**
     * @brief string get_memberInfo search members by membership number
     * @param membership_number
     * @return The member information
     */
    QStringList get_memberInfo(QString membership_number) const;
    /**
     * @brief get_memberPurchases searches by membership number
     * @param membership_number
     * @return The member purchases information
     */
    QVector<QStringList> get_memberPurchases(QString membership_number) const;
    /**
     * @brief get_itemInfo
     * @param item_name
     * @return The item information (quantity, name)
     */
    QStringList get_itemInfo(QString item_name) const;
    /**
     * @brief updates the total Amount Spent by using the membership number
     * @param membership_number
     * @param totalAmountSpent
     */
    void update_totalAmountSpent(QString membership_number, QString totalAmountSpent) const;
    /**
     * @brief updates  the rebate amount by using the membership number
     * @param membership_number
     * @param rebate_amount
     */
    void update_rebateAmount(QString membership_number, QString rebate_amount) const;
    /**
     * @brief insert data in the the inventory
     * @param item_name
     * @param num_of_items
     * @param sell_quantity
     * @param total_revenue
     */
    void insert_row_in_inventory(QString item_name, QString num_of_items, QString sell_quantity, QString total_revenue) const;
    /**
     * @brief deletes data in the the inventory
     * @param item_name
     */
    void delete_row_in_inventory(QString item_name) const;
    /**
     * @brief add item to the inventory
     * @param item_name
     * @param item_price
     */
    void add_item(QString item_name, QString item_price) const;
    /**
     * @brief deletes item to the inventory
     * @param item_name
     */
    void delete_item(QString item_name) const;
    /**
     * @brief updates item in the inventory
     * @param item_name
     * @param item_price
     */
    void update_item(QString item_name, QString item_price) const;
    /**
     * @brief check if item exist in the inventory
     * @param item_name
     */
    bool check_item_existance(QString item_name) const;
    /**
     * @brief check_item_existance
     * @param item_name
     * @param item_id
     */
    bool check_item_existance(QString item_name, QString item_id) const;
    /**
     * @brief adds a member to the database
     * @param member_name
     * @param member_type
     */
    void add_member(QString member_name, QString member_type) const;
    /**
     * @brief deletes a member
     * @param member_name
     * @param membership_id
     */
    void delete_member(QString member_name, QString membership_id) const;
    /**
     * @brief check member existance by membership number
     * @param membership_number
     * @return
     */
    bool check_member_existance(QString membership_number) const;
    /**
     * @brief check member existance
     * @param member_name
     * @param membership_number
     * @return
     */
    bool check_member_existance(QString member_name, QString membership_number) const;
    /**
     * @brief add member purchase
     * @param membership_number
     * @param product
     * @param price
     * @param quantity
     * @param date
     */
    void add_member_purchase(QString membership_number, QString product, QString price, QString quantity, QString date) const;

    QVector<PurchaseData> get_report_all_items();
    QVector<PurchaseData> get_report_all_purchases();
    QVector<PurchaseData> get_report_purchases_by_date(QDate date);
    QVector<Member> get_report_expired_memberships_by_month(int month);
    QVector<MemberPurchaseData> get_report_all_purchases_per_member();

};

#endif // DATABASE_MANAGER_H
