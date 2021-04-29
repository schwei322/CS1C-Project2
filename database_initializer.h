#ifndef DATABASE_INITIALIZER_H
#define DATABASE_INITIALIZER_H

#include <QSqlDatabase>



class Database_initializer
{
    static bool isDataBaseInitialized;
    static QSqlDatabase database;
public:
    Database_initializer();
    bool Database_initializer::getDatabase(QSqlDatabase &database);
};

#endif // DATABASE_INITIALIZER_H
