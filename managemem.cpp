#include "managemem.h"
#include "ui_managemem.h"
#include "admin.h"

#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QSqlQueryModel>

ManageMem::ManageMem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageMem)
{
    ui->setupUi(this);
}

ManageMem::~ManageMem()
{
    delete ui;
}

void ManageMem::on_pushButton_load_clicked()
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

    sql_query.prepare("select * from membership");


    sql_query.exec();

    modal->setQuery(sql_query);
    ui->tableView->setModel(modal);

    qDebug() << (modal->rowCount());

    database.close();
}

void ManageMem::on_pushButton_add_clicked()
{
    this->addDialogWindow = new AddDialog();
    this->addDialogWindow->show();
}

void ManageMem::on_pushButton_delete_clicked()
{
    this->deleteDialogWindow = new DeleteDialog();
    this->deleteDialogWindow->show();
}
