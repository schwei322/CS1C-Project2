#include <QTableWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    QStringList dateOptions;

    dateOptions << "All days" << "Day 1" << "Day 2" << "Day 3" << "Day 4" << "Day 5" << "Day 6" << "Day 7";

    QVector<PurchaseData> purchaseDataList;

    int totalRevenue = 0;

    int selectionIndex = dateOptions.indexOf(this->ui->salesFilterSelect->currentText());
    if (selectionIndex == 0)
    {
        purchaseDataList = this->database_manager.get_report_all_purchases();

        QVector<PurchaseData> newPurchaseDataList;
        QVector<QString> temp;

        for(PurchaseData& data : purchaseDataList)
        {
           if (!temp.contains(data.getProduct()))
           {
               PurchaseData item;

               item.setDate("");
               item.setMembershipNumber(0);
               item.setPrice(data.getPrice());
               item.setProduct(data.getProduct());
               item.setQuantity(0);

               newPurchaseDataList.append(item);
               temp.append(data.getProduct());
           }
        }

        for(PurchaseData& newListData : newPurchaseDataList)
        {
            for (PurchaseData& oldListData : purchaseDataList)
            {
                if (newListData.getProduct() == oldListData.getProduct())
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
            revenue->setData(Qt::EditRole, "$" + QString::number(data.getPrice() * data.getQuantity()));
            revenue->setTextAlignment(Qt::AlignRight);
            this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 2, revenue);

            totalRevenue += data.getPrice() * data.getQuantity();
        }
    }
    else
    {
        QDate date = QDate(2021, 4, dateOptions.indexOf(this->ui->salesFilterSelect->currentText()));

        purchaseDataList = this->database_manager.get_report_purchases_by_date(date);

        for(PurchaseData& data : purchaseDataList)
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
            revenue->setData(Qt::EditRole, "$" + QString::number(data.getPrice() * data.getQuantity()));
            revenue->setTextAlignment(Qt::AlignRight);
            this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 2, revenue);

            totalRevenue += data.getPrice() * data.getQuantity();
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

    int selectionIndex = dateOptions.indexOf(this->ui->salesFilterSelect->currentText());
    if (selectionIndex > 0 && selectionIndex < dateOptions.size())
    {
        QDate date = QDate(2021, 4, dateOptions.indexOf(this->ui->salesFilterSelect->currentText()));

        purchaseDataList = this->database_manager.get_report_purchases_by_date(date);
    }
    else
    {
        purchaseDataList = this->database_manager.get_report_all_purchases();
    }

    QVector<int> temp;
    for(PurchaseData& data : purchaseDataList)
    {
        if (!temp.contains(data.getMembershipNumber()))
        {
            this->ui->salesTable2->insertRow(this->ui->salesTable2 ->rowCount());

            this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 0, new QTableWidgetItem(this->database_manager.get_member_name_from_id(data.getMembershipNumber())));

            QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
            membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
            this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 1, membershipNumber);

            temp.append(data.getMembershipNumber());
        }
    }

    this->ui->salesShoppersDisplay->setText(QString::number(temp.size()));
}

void MainWindow::displayMembersTotalPurchase()
{

    this->ui->membersTable->setRowCount(0);

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
            float Spent = oldListData.getQuantity()* oldListData.getPrice();


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
        this->ui->membersTable->insertRow(this->ui->membersTable ->rowCount());

        QTableWidgetItem  *name = new QTableWidgetItem;
        name->setData(Qt::EditRole, data.getName());
        name->setToolTip(data.getName());
        this->ui->membersTable->setItem(this->ui->membersTable->rowCount() - 1, 0, name);

        QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
        membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
        membershipNumber->setTextAlignment(Qt::AlignRight);
        this->ui->membersTable->setItem(this->ui->membersTable->rowCount() - 1, 1, membershipNumber);

        QTableWidgetItem  *revenue = new QTableWidgetItem;
        revenue->setData(Qt::EditRole, "$" + QString::number(data.getTotalAmountSpent()));
        revenue->setTextAlignment(Qt::AlignRight);
        this->ui->membersTable->setItem(this->ui->membersTable->rowCount() - 1, 2, revenue);

        QTableWidgetItem  *rebate = new QTableWidgetItem;
        rebate->setData(Qt::EditRole, "$" + QString::number(data.getTotalAmountSpent() * 0.02));
        rebate->setTextAlignment(Qt::AlignRight);
        this->ui->membersTable->setItem(this->ui->membersTable->rowCount() - 1, 3, rebate);
    }
        //totalRevenue += data.getPrice() * data.getQuantity();

}

void MainWindow::on_memberRebatesBtn_clicked()
{
    this->checkRabateswindow = new checkRabates();
    this->checkRabateswindow->show();
}
