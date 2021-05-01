#ifndef DATABASE_INITIALIZER_H
#define DATABASE_INITIALIZER_H

#include <QSqlDatabase>



class Database_initializer
{
    static bool isDataBaseInitialized;
    static QSqlDatabase database;
public:
    Database_initializer();
    bool getDatabase(QSqlDatabase &database);
};
#endif // DATABASE_INITIALIZER_H
