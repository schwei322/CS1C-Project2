#include "expmonth.h"
#include <QString>
#include "ui_expmonth.h"
#include <QString>
#include <string.h>
#include "database_manager.h"
#include <QtDebug>


expMonth::expMonth(QWidget *parent, DatabaseManager *dbm) :
    QDialog(parent),
    ui(new Ui::expMonth)
{
    this->dbm = dbm;
    ui->setupUi(this);
}

expMonth::~expMonth()
{
    delete ui;
}


void expMonth::on_comboBox_currentIndexChanged(const QString &arg1)
{
    std::string str = arg1.toStdString();
    uint month = 0;
    if(str == "January")
    {
        month = 1;
    }
    else if(str == "February")
    {
        month = 2;
    }
    else if(str == "March")
    {
        month = 3;
    }
    else if(str == "April")
    {
        month = 4;
    }
    else if(str == "May")
    {
        month = 5;
    }
    else if(str == "June")
    {
        month = 6;
    }
    else if(str == "July")
    {
        month = 7;
    }
    else if(str == "August")
    {
        month = 8;
    }
    else if(str == "September")
    {
        month = 9;
    }
    else if(str == "October")
    {
        month = 10;
    }
    else if(str == "November")
    {
        month = 11;
    }
    else if(str == "December")
    {
        month = 12;
    }

    if (month != 0)
    {
        if(dbm != nullptr)
        {
            QVector<Member> members = dbm->get_report_expired_memberships_from_month(month);
            for(Member member : members)
            {
                member.calc_annual_dues();
            }
        }
        else
        {
            qDebug() << "dbm was not initialized\n";
        }
    }
    else
    {
        qDebug() << "invalid month\n";
    }
}

