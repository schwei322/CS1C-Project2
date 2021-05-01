#include "deletedialog.h"
#include "ui_deletedialog.h"

DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::on_buttonBox_accepted()
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

    QString Name, Number;
    Name = ui->txt_name->text();
    Number = ui->txt_num->text();

    QSqlQuery sql_query;

    if(!sql_query.exec("delete from membership where Name = '"+Name+"' and MembershipNumber = '"+Number+"'"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Delete Successful!";
    }


    database.close();
}
