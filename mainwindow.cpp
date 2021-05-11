#include <QTableWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expmonth.h"

#ifdef QT_DEBUG
bool debugMode = true;
#else
bool debugMode = false;
#endif

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), database_manager()
{
    ui->setupUi(this);

    ui->salesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->salesTable->verticalHeader()->setVisible(false);
    ui->salesTable->setSortingEnabled(true);

    ui->salesTable2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->salesTable2->verticalHeader()->setVisible(false);
    ui->salesTable2->setSortingEnabled(true);

    ui->membersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->adminInventoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->adminMembersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    this->displaySales();

    if (debugMode)
    {
        ui->loginPanel->hide();
    }
    else
    {
        ui->loginPanel->raise();
        ui->adminBtn->hide();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userLogin()
{
    const QString adminUsername = "admin";
    const QString adminPassword = "admin";
    const QString managerUsername = "manager";
    const QString managerPassword = "manager";

    if (this->ui->usernameInput->text() == adminUsername && this->ui->passwordInput->text() == adminPassword)
    {
        this->ui->adminBtn->show();
        this->ui->loginPanel->hide();
    }
    else if (this->ui->usernameInput->text() == managerUsername && this->ui->passwordInput->text() == managerPassword)
    {
        this->ui->adminBtn->hide();
        this->ui->loginPanel->hide();
    }
}

void MainWindow::userLogout()
{
    this->ui->adminBtn->hide();
    this->ui->loginPanel->show();
}

void MainWindow::displaySales()
{
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");
    this->ui->membersBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");

    this->ui->sales->raise();

    this->displaySalesByDate();
    this->displayMembersByDate();
}

void MainWindow::displayMembers()
{
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->membersBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");

    this->ui->members->raise();
}

void MainWindow::displayAdmin()
{
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->membersBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");

    this->ui->admin->raise();
}

void MainWindow::displaySalesByDate()
{
    this->ui->salesTable->setRowCount(0);

    QStringList memberOptions;

    memberOptions << "All members" << "Regular" << "Executive";

    int memberSelectionIndex = memberOptions.indexOf(this->ui->membersFilterSelect->currentText());

    QStringList dateOptions;

    dateOptions << "All days" << "Day 1" << "Day 2" << "Day 3" << "Day 4" << "Day 5" << "Day 6" << "Day 7";

    QVector<PurchaseData> purchaseDataList;

    double totalRevenue = 0;

    int selectionIndex = dateOptions.indexOf(this->ui->salesFilterSelect->currentText());
    if (selectionIndex == 0)
    {
        purchaseDataList = this->database_manager.get_report_all_purchases();

        QVector<PurchaseData> newPurchaseDataList;

        QVector<QString> tempProductVec;
        for(PurchaseData& data : purchaseDataList)
        {
            QStringList memberInfo = this->database_manager.get_memberInfo(QString::number(data.getMembershipNumber()));

            if (!tempProductVec.contains(data.getProduct()) && (memberSelectionIndex == 0 || (memberSelectionIndex != 0 && memberOptions[memberSelectionIndex] == memberInfo.at(2))))
            {
                PurchaseData purchase;

                purchase.setDate("");
                purchase.setMembershipNumber(0);
                purchase.setPrice(data.getPrice());
                purchase.setProduct(data.getProduct());
                purchase.setQuantity(0);

                newPurchaseDataList.append(purchase);
                tempProductVec.append(data.getProduct());
            }
        }

        for(PurchaseData& newListData : newPurchaseDataList)
        {
            for (PurchaseData& oldListData : purchaseDataList)
            {
                if (newListData == oldListData)
                {
                    newListData.setQuantity(newListData.getQuantity() + oldListData.getQuantity());
                }
            }
        }

        for(PurchaseData& data : newPurchaseDataList)
        {
            this->ui->salesTable->insertRow(this->ui->salesTable ->rowCount());

            QTableWidgetItem  *product = new QTableWidgetItem;
            product->setData(Qt::EditRole, data.getProduct());
            product->setToolTip(data.getProduct());
            this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 0, product);

            QTableWidgetItem  *quantity = new QTableWidgetItem;
            quantity->setData(Qt::EditRole, data.getQuantity());
            quantity->setTextAlignment(Qt::AlignRight);
            this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 1, quantity);

            QTableWidgetItem  *revenue = new QTableWidgetItem;
            revenue->setData(Qt::EditRole, data.getPrice() * data.getQuantity());
            revenue->setTextAlignment(Qt::AlignRight);
            this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 2, revenue);

            totalRevenue += data.getPrice() * data.getQuantity();
        }
    }
    else
    {
        QDate date = QDate(2021, 4, dateOptions.indexOf(this->ui->salesFilterSelect->currentText()));

        purchaseDataList = this->database_manager.get_report_purchases_by_date(date);

        QVector<int> tempMemberVec;
        for(PurchaseData& data : purchaseDataList)
        {
            QStringList memberInfo = this->database_manager.get_memberInfo(QString::number(data.getMembershipNumber()));

            if ((memberSelectionIndex == 0 && !tempMemberVec.contains(data.getMembershipNumber()))
                    || (memberSelectionIndex != 0 && !tempMemberVec.contains(data.getMembershipNumber()) && memberOptions[memberSelectionIndex] == memberInfo.at(2)))
            {
                tempMemberVec.append(data.getMembershipNumber());
            }
        }

        for(PurchaseData& data : purchaseDataList)
        {
            if (tempMemberVec.contains(data.getMembershipNumber()))
            {
                this->ui->salesTable->insertRow(this->ui->salesTable ->rowCount());

                QTableWidgetItem  *product = new QTableWidgetItem;
                product->setData(Qt::EditRole, data.getProduct());
                product->setToolTip(data.getProduct());
                this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 0, product);

                QTableWidgetItem  *quantity = new QTableWidgetItem;
                quantity->setData(Qt::EditRole, data.getQuantity());
                quantity->setTextAlignment(Qt::AlignRight);
                this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 1, quantity);

                QTableWidgetItem  *revenue = new QTableWidgetItem;
                revenue->setData(Qt::EditRole, data.getPrice() * data.getQuantity());
                revenue->setTextAlignment(Qt::AlignRight);
                this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 2, revenue);

                totalRevenue += data.getPrice() * data.getQuantity();
            }
        }
    }

    this->ui->salesRevDisplay->setText("$" + QString::number(totalRevenue));
}

void MainWindow::displayMembersByDate()
{
    this->ui->salesTable2->setRowCount(0);

    QStringList dateOptions;

    dateOptions << "All days" << "Day 1" << "Day 2" << "Day 3" << "Day 4" << "Day 5" << "Day 6" << "Day 7";

    QVector<PurchaseData> purchaseDataList;

    int dataSelectionIndex = dateOptions.indexOf(this->ui->salesFilterSelect->currentText());
    if (dataSelectionIndex > 0 && dataSelectionIndex < dateOptions.size())
    {
        QDate date = QDate(2021, 4, dateOptions.indexOf(this->ui->salesFilterSelect->currentText()));

        purchaseDataList = this->database_manager.get_report_purchases_by_date(date);
    }
    else
    {
        purchaseDataList = this->database_manager.get_report_all_purchases();
    }

    QStringList memberOptions;

    memberOptions << "All members" << "Regular" << "Executive";

    int memberSelectionIndex = memberOptions.indexOf(this->ui->membersFilterSelect->currentText());

    QVector<int> tempMemberVec;
    for(PurchaseData& data : purchaseDataList)
    {
        QStringList memberInfo = this->database_manager.get_memberInfo(QString::number(data.getMembershipNumber()));

        if ((memberSelectionIndex == 0 && !tempMemberVec.contains(data.getMembershipNumber()))
                || (memberSelectionIndex != 0 && !tempMemberVec.contains(data.getMembershipNumber()) && memberOptions[memberSelectionIndex] == memberInfo.at(2)))
        {

            this->ui->salesTable2->insertRow(this->ui->salesTable2 ->rowCount());

            this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 0, new QTableWidgetItem(memberInfo.at(0)));

            QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
            membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
            membershipNumber->setTextAlignment(Qt::AlignRight);
            this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 1, membershipNumber);

            tempMemberVec.append(data.getMembershipNumber());
        }
    }

    this->ui->salesShoppersDisplay->setText(QString::number(tempMemberVec.size()));
}

void MainWindow::on_memberExpirationBtn_clicked()
{
    expirationMonth = new expMonth(this, &this->database_manager);
    expirationMonth->show();
}

void MainWindow::on_salesSearchInput_editingFinished()
{

}
