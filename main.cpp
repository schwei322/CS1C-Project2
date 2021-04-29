#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "database_manager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    /**********************************************/
    // Querying database using database_manager class.

    // data base initializer is so that we use (or begin to use) the same database connect across our classes and in our main for the "bulk_club_database.db"
    Database_initializer database_initializer;
    Database_manager db = {database_initializer};

    qDebug() << db.get_memberInfo("88888") << "\n";
    //qDebug() <<db.get_memberPurchases("88888") << "\n";
    //qDebug() <<db.get_itemInfo("Coke");

    //db.update_totalAmountSpent("88888", "123");
    //db.insert_row_in_inventory("a_name", "a_sellQuantity", "a_totalRevenue");
    //db.delete_row_in_inventory("a_name");

    // sqlite code
        QSqlDatabase database;
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("MyDataBase.db");
        if (!database.open())
        {
            qDebug() << "Error: Failed to connect database." << database.lastError();
        }
        else
        {
            qDebug() << "Succeed to connect database." ;
        }
    /**********************************************/

        QSqlQuery sql_query;
        if(!sql_query.exec("create table student(id int primary key, name text, age int)"))
        {
            qDebug() << "Error: Fail to create table."<< sql_query.lastError();
        }
        else
        {
            qDebug() << "Table created!";
        }
        //insert data
        if(!sql_query.exec("INSERT INTO student VALUES(1, \"Ming\", 23)"))
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted Ming!";
        }
        if(!sql_query.exec("INSERT INTO student VALUES(2, \"Farhan\", 23)"))
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "inserted Farhan!";
        }

        //edit data
        sql_query.exec("update student set name = \"Dayana\" where id = 1");
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "update Ming to Dayana!";
        }

        //check data
        sql_query.exec("select * from student");
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            while(sql_query.next())
            {
                int id = sql_query.value(0).toInt();
                QString name = sql_query.value(1).toString();
                int age = sql_query.value(2).toInt();
                qDebug()<<QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
            }
        }

        //delete data
        sql_query.exec("delete from student where id = 1");
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            qDebug()<<"deleted!";
        }

        //delete table
        sql_query.exec("drop table student");
        if(sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "table cleared";
        }

        //close database
        database.close();

    exit(0); // Prevents window from opening
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
