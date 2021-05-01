#include "deleteitem.h"
#include "ui_deleteitem.h"

DeleteItem::DeleteItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteItem)
{
    ui->setupUi(this);
}

DeleteItem::~DeleteItem()
{
    delete ui;
}

void DeleteItem::on_buttonBox_accepted()
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

    QString Name, Price;
    Name = ui->txt_name->text();
    Price = ui->txt_price->text();

    QSqlQuery sql_query;

    if(!sql_query.exec("delete from Items where Name = '"+Name+"' and Price = '"+Price+"'"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Delete Successful!";
    }


    database.close();
}
