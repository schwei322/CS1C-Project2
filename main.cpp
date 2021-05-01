#include "mainwindow.h"

#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();


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
        QString input111 = "12121";
        QStringList membersData;
        QSqlQuery sql_query;
        QString command = "SELECT * FROM Membership WHERE MembershipNumber =" + input111;
        if(sql_query.exec(command))
        {
            while(sql_query.next())
            {

                for(int i = 0; i < 4 ; i++)
                {
                    membersData.append(sql_query.value(i).toString());
                }
                qDebug() << membersData;
            }
        }


        /*
        sql_query.exec("SELECT * FROM Membership WHERE MembershipNumber =" + input111");
        while(sql_query.next())
        {
            QString name = sql_query.value(0).toString();
            int number = sql_query.value(1).toInt();
            QString type = sql_query.value(2).toString();
            QString date = sql_query.value(3).toString();
            qDebug()<<QString("Name:%0    Number:%1    type:%2    Date:%3").arg(name).arg(number).arg(type).arg(date);
        }*/
/*
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
*/

        //close database
        database.close();
    return a.exec();
}
