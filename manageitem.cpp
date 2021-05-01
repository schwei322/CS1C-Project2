#include "manageitem.h"
#include "ui_manageitem.h"

#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QSqlQueryModel>

ManageItem::ManageItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageItem)
{
    ui->setupUi(this);


}

ManageItem::~ManageItem()
{
    delete ui;
}

void ManageItem::on_pushButton_clicked()
{
    this->addItemWindow = new AddItem();
    this->addItemWindow->show();
}

void ManageItem::on_pushButton_2_clicked()
{
    this->deleteItemWindow = new DeleteItem();
    this->deleteItemWindow->show();
}


void ManageItem::on_pushButton_3_clicked()
{
    this->updateItemWindow = new UpdateItem();
    this->updateItemWindow->show();
}

void ManageItem::on_pushButton_4_clicked()
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
    QSqlQueryModel *modal = new QSqlQueryModel;
    QSqlQuery sql_query;

    sql_query.prepare("select * from Items");


    sql_query.exec();

    modal->setQuery(sql_query);
    ui->tableView->setModel(modal);

    qDebug() << (modal->rowCount());

    database.close();

}
