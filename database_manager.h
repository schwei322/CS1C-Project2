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

const QString databasePath = QProcessEnvironment::systemEnvironment().value("DBPATH");

/// Class instance connects to Bulk Club's database.
///
/// Has methods that can change database fields.
class DatabaseManager
{
private:
    QSqlDatabase database;
    QVector<PurchaseData> issue_items_query(QString command);
    QVector<PurchaseData> issue_purchases_query(QString command);
    QVector<PurchaseData> aggregate_items_data(QSqlQuery query);
    QVector<PurchaseData> aggregate_purchases_data(QSqlQuery query);
    QVector<Member> aggregate_member_data(QSqlQuery query);

public:
    DatabaseManager();
    ~DatabaseManager();

    QStringList get_memberInfo(QString membership_number) const;
    QVector<QStringList> get_memberPurchases(QString membership_number) const;
    QStringList get_itemInfo(QString item_name) const;

    void update_totalAmountSpent(QString membership_number, QString totalAmountSpent) const;
    void update_rebateAmount(QString membership_number, QString rebate_amount) const;
    void insert_row_in_inventory(QString item_name, QString num_of_items, QString sell_quantity, QString total_revenue) const;
    void delete_row_in_inventory(QString item_name) const;

    void add_item(QString item_name, QString item_price) const;
    void delete_item(QString item_name, QString item_id) const;
    void update_item(QString item_name, QString item_price) const;
    bool check_item_existance(QString item_name) const;
    bool check_item_existance(QString item_name, QString item_id) const;

    void add_member(QString member_name, QString member_type) const;
    void delete_member(QString member_name, QString membership_id) const;
    bool check_member_existance(QString membership_number) const;
    bool check_member_existance(QString member_name, QString membership_number) const;

    void add_member_purchase(QString membership_number, QString product, QString price, QString quantity, QString date) const;

    QVector<PurchaseData> get_report_all_items();
    QVector<PurchaseData> get_report_all_purchases();
    QVector<PurchaseData> get_report_purchases_by_date(QDate date);
    QVector<Member> get_report_expired_memberships_by_month(int month);
    QVector<MemberPurchaseData> get_report_all_purchases_per_member();

};

#endif // DATABASE_MANAGER_H
