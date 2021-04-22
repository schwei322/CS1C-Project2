#include "item.h"
#include <QApplication>
//添加头文件
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

Item::Item()
{
    itemName = "None";
    itemPrice = 0;
    salesQual = 0;
}

Item::Item(QString name,  double price, double quantity)
{
    this->itemName = name;
    this->itemPrice = price;
    this->salesQual = quantity;
}
double Item::calc_totalRevenue(double itemPrice, double salesQual)
{
    return itemPrice * salesQual;
}

int main()
{
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


        database.close();
        return 0;
}
