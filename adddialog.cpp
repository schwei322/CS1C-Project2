#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_buttonBox_accepted()
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

    QString Name, Number, Type, Date;
    Name = ui->txt_name->text();
    Number = ui->txt_num->text();
    Type = ui->txt_type->text();
    Date = ui->txt_type->text();

    QSqlQuery sql_query;

    if(!sql_query.exec("insert into membership (Name, MembershipNumber, Type, ExpirationDate) values('"+Name+"','"+Number+"','"+Type+"','"+Date+"')"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "Inserted Successful!";
    }


    database.close();
}
