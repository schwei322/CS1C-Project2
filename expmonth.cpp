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

    //ui->tableWidget
}

expMonth::~expMonth()
{
    delete ui;
}


void expMonth::on_comboBox_currentIndexChanged()
{
    this->ui->tableWidget->setRowCount(0);

    uint month = this->ui->comboBox->currentIndex() + 1;
    if (month > 0 && month < 13)
    {
        if(dbm != nullptr)
        {
            QVector<Member*> members = dbm->get_report_expired_memberships_from_month(month);
            for(Member* member : members)
            {
                this->ui->tableWidget->insertRow(this->ui->tableWidget ->rowCount());

                QTableWidgetItem  *name = new QTableWidgetItem;
                qDebug() << member->get_name() << " THIS WAS THE NAME";
                name->setData(Qt::EditRole, member->get_name());
                name->setTextAlignment(Qt::AlignRight);
                this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 0, name);

                QTableWidgetItem  *membershipType = new QTableWidgetItem;
                membershipType->setData(Qt::EditRole, member->get_membership_type());
                membershipType->setTextAlignment(Qt::AlignRight);
                this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 1, membershipType);

                QTableWidgetItem  *costToRenew = new QTableWidgetItem;
                costToRenew->setData(Qt::EditRole, "$" + QString::number(member->calc_annual_dues()));
                costToRenew->setTextAlignment(Qt::AlignRight);
                this->ui->tableWidget->setItem(this->ui->tableWidget->rowCount() - 1, 2, costToRenew);
                delete member;
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

