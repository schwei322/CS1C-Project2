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

const double TAX = 0.0775;

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

    ui->memberTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memberTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memberTable->verticalHeader()->setVisible(false);

    ui->memberRebatesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memberRebatesTable->verticalHeader()->setVisible(false);

    ui->expiredRegularTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->expiredRegularTable->verticalHeader()->setVisible(false);
    ui->expiredRegularTable->setSortingEnabled(true);

    ui->expiredExecutiveTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->expiredExecutiveTable->verticalHeader()->setVisible(false);
    ui->expiredExecutiveTable->setSortingEnabled(true);    

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

    this->ui->memberTable->setRowCount(0);

    QVector<MemberPurchaseData> purchaseDataList = this->database_manager.get_report_all_purchases_per_member();

    QVector<MemberPurchaseData> newPurchaseDataList;
    QVector<int> tempMemberVec;

    for(MemberPurchaseData& data : purchaseDataList)
    {
       if (!tempMemberVec.contains(data.getMembershipNumber()))
       {
           MemberPurchaseData purchaseData;

           purchaseData.setName(data.getName());
           purchaseData.setMembershipNumber(data.getMembershipNumber());
           purchaseData.setMembershipType(data.getMembershipType());
           purchaseData.setExpirationDate(data.getExpirationDate());
           purchaseData.setPrice(data.getPrice());
           purchaseData.setQuantity(data.getQuantity());

           newPurchaseDataList.append(purchaseData);
           tempMemberVec.append(data.getMembershipNumber());
       }
    }

    for(MemberPurchaseData& newListData : newPurchaseDataList)
    {
        for (MemberPurchaseData& oldListData : purchaseDataList)
        {
            if (newListData.getMembershipNumber() == oldListData.getMembershipNumber())
            {
                newListData.setTotalSpent(newListData.getTotalSpent()  + (oldListData.getQuantity()* oldListData.getPrice()));
            }
        }
    }

    double grandTotal = 0;
    for(MemberPurchaseData& data : newPurchaseDataList)
    {
        this->ui->memberTable->insertRow(this->ui->memberTable ->rowCount());

        QTableWidgetItem  *name = new QTableWidgetItem;
        name->setData(Qt::EditRole, data.getName());
        name->setToolTip(data.getName());
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 0, name);

        QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
        membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
        membershipNumber->setTextAlignment(Qt::AlignRight);
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 1, membershipNumber);

        QString membershipType = data.getMembershipType();
        QTableWidgetItem  *type = new QTableWidgetItem;
        type->setData(Qt::EditRole, membershipType);
        type->setTextAlignment(Qt::AlignRight);
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 2, type);

        QTableWidgetItem  *date = new QTableWidgetItem;
        date->setData(Qt::EditRole, data.getExpirationDate());
        date->setTextAlignment(Qt::AlignRight);
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 3, date);

        double totalSpentAmount = data.getTotalSpent() + (data.getTotalSpent() * TAX);
        QTableWidgetItem  *spent = new QTableWidgetItem;
        spent->setData(Qt::EditRole, "$" + QString::number(totalSpentAmount, 'f', 2));
        spent->setTextAlignment(Qt::AlignRight);
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 4, spent);

        this->database_manager.update_totalAmountSpent(QString::number(data.getMembershipNumber()), QString::number(totalSpentAmount));
        this->database_manager.update_rebateAmount(QString::number(data.getMembershipNumber()), QString::number(membershipType == "Executive" ? ((totalSpentAmount - (totalSpentAmount * TAX)) * 0.02) : 0));

        grandTotal += totalSpentAmount;
    }

    this->ui->memberTotalDisplay->setText("$" + QString::number(grandTotal, 'f', 2));

    this->ui->memberMainPanel->raise();
    this->ui->memberBackBtn->hide();

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

    this->ui->salesRevDisplay->setText("$" + QString::number(totalRevenue + (totalRevenue * TAX), 'f', 2));
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

void MainWindow::on_memberBackBtn_clicked()
{
    this->ui->memberMainPanel->raise();
    this->ui->memberSearchLabel->show();
    this->ui->memberSearchInput->show();
    this->ui->memberBackBtn->hide();
}

void MainWindow::on_memberRebatesBtn_clicked()
{
    this->ui->memberRebatesTable->setRowCount(0);

    QVector<MemberPurchaseData> purchaseDataList = this->database_manager.get_report_all_purchases_per_member();

    QVector<MemberPurchaseData> newPurchaseDataList;
    QVector<int> tempMemberVec;

    for(MemberPurchaseData& data : purchaseDataList)
    {
       if (!tempMemberVec.contains(data.getMembershipNumber()) && data.getMembershipType() == "Executive")
       {
           MemberPurchaseData purchaseData;

           purchaseData.setName(data.getName());
           purchaseData.setMembershipNumber(data.getMembershipNumber());
           purchaseData.setTotalSpent(data.getTotalSpent());
           purchaseData.setRebateAmount(data.getRebateAmount());

           newPurchaseDataList.append(purchaseData);
           tempMemberVec.append(data.getMembershipNumber());
       }
    }

    for(MemberPurchaseData& data : newPurchaseDataList)
    {
        this->ui->memberRebatesTable->insertRow(this->ui->memberRebatesTable ->rowCount());

        QTableWidgetItem  *name = new QTableWidgetItem;
        name->setData(Qt::EditRole, data.getName());
        name->setToolTip(data.getName());
        this->ui->memberRebatesTable->setItem(this->ui->memberRebatesTable->rowCount() - 1, 0, name);

        QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
        membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
        membershipNumber->setTextAlignment(Qt::AlignRight);
        this->ui->memberRebatesTable->setItem(this->ui->memberRebatesTable->rowCount() - 1, 1, membershipNumber);

        QTableWidgetItem  *spent = new QTableWidgetItem;
        spent->setData(Qt::EditRole, "$" + QString::number(data.getTotalSpent(), 'f', 2));
        spent->setTextAlignment(Qt::AlignRight);
        this->ui->memberRebatesTable->setItem(this->ui->memberRebatesTable->rowCount() - 1, 2, spent);

        QTableWidgetItem  *rebate = new QTableWidgetItem;
        rebate->setData(Qt::EditRole, "$" + QString::number(data.getRebateAmount(), 'f', 2));
        rebate->setTextAlignment(Qt::AlignRight);
        this->ui->memberRebatesTable->setItem(this->ui->memberRebatesTable->rowCount() - 1, 3, rebate);
    }

    this->ui->memberRebatesPanel->raise();
    this->ui->memberSearchLabel->hide();
    this->ui->memberSearchInput->hide();
    this->ui->memberBackBtn->show();
}

void MainWindow::on_memberExpirationBtn_clicked()
{
    // Workaround to get the table to load January by default
    this->ui->expirationMonthSelect->setCurrentIndex(1);
    this->ui->expirationMonthSelect->setCurrentIndex(0);

    this->ui->memberExpirationPanel->raise();
    this->ui->memberSearchLabel->hide();
    this->ui->memberSearchInput->hide();
    this->ui->memberBackBtn->show();
}

void MainWindow::on_expirationMonthSelect_currentIndexChanged()
{
    this->ui->expiredRegularTable->setRowCount(0);
    this->ui->expiredExecutiveTable->setRowCount(0);

    int month = this->ui->expirationMonthSelect->currentIndex() + 1;
    QVector<Member> members = this->database_manager.get_report_expired_memberships_by_month(month);

    for(Member& member : members)
    {
        if (member.get_membership_type() == "Regular")
        {
            this->ui->expiredRegularTable->insertRow(this->ui->expiredRegularTable ->rowCount());

            QTableWidgetItem  *name = new QTableWidgetItem;
            name->setData(Qt::EditRole, member.get_name());
            this->ui->expiredRegularTable->setItem(this->ui->expiredRegularTable->rowCount() - 1, 0, name);

            QTableWidgetItem  *costToRenew = new QTableWidgetItem;
            costToRenew->setData(Qt::EditRole, "$65");
            costToRenew->setTextAlignment(Qt::AlignRight);
            this->ui->expiredRegularTable->setItem(this->ui->expiredRegularTable->rowCount() - 1, 1, costToRenew);
        }
        else
        {
            this->ui->expiredExecutiveTable->insertRow(this->ui->expiredExecutiveTable ->rowCount());

            QTableWidgetItem  *name = new QTableWidgetItem;
            name->setData(Qt::EditRole, member.get_name());
            this->ui->expiredExecutiveTable->setItem(this->ui->expiredExecutiveTable->rowCount() - 1, 0, name);

            QTableWidgetItem  *costToRenew = new QTableWidgetItem;
            costToRenew->setData(Qt::EditRole, "$120");
            costToRenew->setTextAlignment(Qt::AlignRight);
            this->ui->expiredExecutiveTable->setItem(this->ui->expiredExecutiveTable->rowCount() - 1, 1, costToRenew);
        }
    }
}
