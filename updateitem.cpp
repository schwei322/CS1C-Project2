#include "updateitem.h"
#include "ui_updateitem.h"

UpdateItem::UpdateItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateItem)
{
    ui->setupUi(this);
}

UpdateItem::~UpdateItem()
{
    delete ui;
}

void UpdateItem::on_buttonBox_accepted()
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

    if(!sql_query.exec("update Items set Price = '"+Price+"' where Name = '"+Name+"' "))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Update Successful!";
    }



    database.close();
}
