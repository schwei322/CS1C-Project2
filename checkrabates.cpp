#include "checkrabates.h"
#include "ui_checkrabates.h"
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QSqlQueryModel>
#include <QTableWidgetItem>

#include <iostream>
using namespace std;

checkRabates::checkRabates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checkRabates), database_manager()
{
    ui->setupUi(this);
}

checkRabates::~checkRabates()
{
    delete ui;
}

void checkRabates::displayRebates()

{


}

void checkRabates::on_pushButton_clicked()
{
    this->ui->rebateTable->setRowCount(0);

    QVector<memberPurchase> memberDataList;

    //QVector<PurchaseData> purchaseDataList;

    //int totalRevenue = 0;

    memberDataList = this->database_manager.get_all_purchases_per_member();

    QVector<memberPurchase> newMemberDataList;
    QVector<int> temp;
    for(memberPurchase& data : memberDataList)
    {
       if (!temp.contains(data.getMembershipNumber()))
       {
           memberPurchase member;

           member.setName(data.getName());
           member.setMembershipNumber(data.getMembershipNumber());
           member.setPrice(0);
           member.setQuantity(0);
           member.setTotalAmountSpent(0);

           newMemberDataList.append(member);
           temp.append(data.getMembershipNumber());
       }


    }

    for(memberPurchase& newListData : newMemberDataList)
    {
        newListData.print();
        for (memberPurchase& oldListData : memberDataList)
        {

            FLOAT Spent = oldListData.getQuantity()* oldListData.getPrice();


            if (newListData.getMembershipNumber() == oldListData.getMembershipNumber())
            {
                cout << "Before: " << newListData.getTotalAmountSpent() << endl;
                cout << "spent: " << Spent << endl;

                newListData.setTotalAmountSpent( newListData.getTotalAmountSpent()  + Spent);

                cout << "After: " << newListData.getTotalAmountSpent() << endl;
            }
        }
    }

    for(memberPurchase& data : newMemberDataList)
    {
        this->ui->rebateTable->insertRow(this->ui->rebateTable ->rowCount());

        QTableWidgetItem  *name = new QTableWidgetItem;
        name->setData(Qt::EditRole, data.getName());
        name->setToolTip(data.getName());
        this->ui->rebateTable->setItem(this->ui->rebateTable->rowCount() - 1, 0, name);

        QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
        membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
        membershipNumber->setTextAlignment(Qt::AlignRight);
        this->ui->rebateTable->setItem(this->ui->rebateTable->rowCount() - 1, 1, membershipNumber);

        QTableWidgetItem  *revenue = new QTableWidgetItem;
        revenue->setData(Qt::EditRole, "$" + QString::number(data.getTotalAmountSpent()));
        revenue->setTextAlignment(Qt::AlignRight);
        this->ui->rebateTable->setItem(this->ui->rebateTable->rowCount() - 1, 2, revenue);

        QTableWidgetItem  *rebate = new QTableWidgetItem;
        rebate->setData(Qt::EditRole, "$" + QString::number(data.getTotalAmountSpent() * 0.02));
        rebate->setTextAlignment(Qt::AlignRight);
        this->ui->rebateTable->setItem(this->ui->rebateTable->rowCount() - 1, 3, rebate);

        //totalRevenue += data.getPrice() * data.getQuantity();
    }



}
