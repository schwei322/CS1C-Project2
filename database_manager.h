#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtDebug>
#include <QVector>
#include "date.h"

/// Class instance connects to Bulk Club's database.
///
/// Has methods that can change database fields.
class Database_manager
{
private:
    QSqlDatabase database;

public:
    Database_manager();
    ~Database_manager();

    void add_member(QString member_name, QString member_type) const;
    void delete_member(QString member_name, QString membership_id) const;
    bool check_member_existance(QString membership_number) const;
    bool check_member_existance(QString member_name, QString membership_number) const;
    QStringList get_memberInfo(QString membership_number) const;
    void add_member_purchase(QString membership_number, QString product, QString price, QString quantity, QString date) const;
    QVector<QStringList> get_memberPurchases(QString membership_number) const;
    QStringList get_itemInfo(QString item_name) const;

    void update_totalAmountSpent(QString membership_number, QString totalAmountSpent) const;
    void insert_row_in_inventory(QString item_name, QString num_of_items, QString sell_quantity, QString total_revenue) const;
    void delete_row_in_inventory(QString item_name) const;
    void add_item(QString item_name, QString item_price) const;
    void delete_item(QString item_name, QString item_id);
    bool check_item_existance(QString item_name);
    bool check_item_existance(QString item_name, QString item_id);
    void update_item(QString item_name, QString item_price);

};
#endif // DATABASE_MANAGER_H
