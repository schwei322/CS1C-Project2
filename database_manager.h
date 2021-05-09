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

const QString databasePath = "C:\\Users\\Dayana Pulido\\Documents\\Saddleback\\Spring 2021\\CS1C\\Project 1\\CS1C-Project2\\bulk_club_database.db";//QProcessEnvironment::systemEnvironment().value("DBPATH");

/// Class instance connects to Bulk Club's database.
///
/// Has methods that can change database fields.
class DatabaseManager
{
private:
    QSqlDatabase database;
    QVector<PurchaseData> issue_purchases_query(QString command);
    QVector<PurchaseData> aggregate_purchases_data(QSqlQuery query);
    QVector<Member*> DatabaseManager::aggregate_member_data(QSqlQuery query);

public:
    DatabaseManager();
    ~DatabaseManager();

    QStringList get_memberInfo(QString membership_number) const;
    QVector<QStringList> get_memberPurchases(QString membership_number) const;
    QStringList get_itemInfo(QString item_name) const;

    void update_totalAmountSpent(QString membership_number, QString totalAmountSpent) const;
    void insert_row_in_inventory(QString item_name, QString num_of_items, QString sell_quantity, QString total_revenue) const;
    void delete_row_in_inventory(QString item_name) const;
    QVector<Member*> DatabaseManager::get_report_expired_memberships_from_month(uint month);

    QString get_member_name_from_id(int id);
    QVector<PurchaseData> get_report_all_purchases();
    QVector<PurchaseData> get_report_purchases_by_date(QDate date);

};

#endif // DATABASE_MANAGER_H
