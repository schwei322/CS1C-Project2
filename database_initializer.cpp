#include "database_initializer.h"
#include <QtDebug>
#include <QSqlError>

Database_initializer::Database_initializer()
{
    if(!isDataBaseInitialized)
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("bulk_club_database.db");
        if (database.open())
        {
            isDataBaseInitialized = true;
        }
        else
        {
            qDebug() << "Error: Failed to connect database." << database.lastError();
        }
    }
}

bool Database_initializer::getDatabase(QSqlDatabase &database)
{
    if(isDataBaseInitialized)
    {
        database = this->database;
    }
    return isDataBaseInitialized;
}
