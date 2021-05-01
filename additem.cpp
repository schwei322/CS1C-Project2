#include "additem.h"
#include "ui_additem.h"

AddItem::AddItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItem)
{
    ui->setupUi(this);
}

AddItem::~AddItem()
{
    delete ui;
}

void AddItem::on_buttonBox_accepted()
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

    if(!sql_query.exec("insert into Items (Name, Price) values('"+Name+"','"+Price+"')"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Inserted Successful!";
    }


    database.close();
}
