#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtDebug>
#include <QVector>

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

    QStringList get_memberInfo(QString membership_number) const;
    QVector<QStringList> get_memberPurchases(QString membership_number) const;
    QStringList get_itemInfo(QString item_name) const;

};
#endif // DATABASE_MANAGER_H
