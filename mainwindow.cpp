#include <QMessageBox>
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

/****************************************************************************//**
 *      Constructor
*******************************************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), database_manager()
{
    ui->setupUi(this);

    ui->salesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->salesTable->verticalHeader()->setVisible(false);

    ui->salesTable2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->salesTable2->verticalHeader()->setVisible(false);

    ui->memberTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memberTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memberTable->verticalHeader()->setVisible(false);

    ui->memberRebatesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->memberRebatesTable->verticalHeader()->setVisible(false);

    ui->expiredRegularTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->expiredRegularTable->verticalHeader()->setVisible(false);

    ui->expiredExecutiveTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->expiredExecutiveTable->verticalHeader()->setVisible(false);

    ui->manageInventoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->manageInventoryTable->verticalHeader()->setVisible(false);

    ui->manageMemberTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->manageMemberTable->verticalHeader()->setVisible(false);

    this->ui->addItemPanel->hide();
    this->ui->delItemPanel->hide();
    this->ui->upItemPanel->hide();

    this->ui->addMemPanel->hide();
    this->ui->delMemPanel->hide();
    this->ui->addPurchasePanel->hide();

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
/*******************************************************************************/



/****************************************************************************//**
 *      Deconstructor
*******************************************************************************/

MainWindow::~MainWindow()
{
    delete ui;
}
/*******************************************************************************/



/****************************************************************************//**
 *      userLogin
*******************************************************************************/

void MainWindow::userLogin()
{
    const QString adminUsername = "admin";
    const QString adminPassword = "admin";
    const QString managerUsername = "manager";
    const QString managerPassword = "manager";

    if (this->ui->usernameInput->text() == adminUsername && this->ui->passwordInput->text() == adminPassword)
    {
        this->ui->admin->show();
        this->ui->adminBtn->show();
        this->ui->loginPanel->hide();
        this->ui->memberTable->setColumnHidden(5, false);
        this->ui->memberTotalPromoDisplay->show();
        this->ui->memberTotalDemoDisplay->show();
    }
    else if (this->ui->usernameInput->text() == managerUsername && this->ui->passwordInput->text() == managerPassword)
    {
        this->ui->admin->hide();
        this->ui->adminBtn->hide();
        this->ui->loginPanel->hide();
        this->ui->memberTable->setColumnHidden(5, true);
        this->ui->memberTotalPromoDisplay->hide();
        this->ui->memberTotalDemoDisplay->hide();
    }

    this->ui->usernameInput->clear();
    this->ui->passwordInput->clear();
}
/*******************************************************************************/



/****************************************************************************//**
 *      userLogout
*******************************************************************************/

void MainWindow::userLogout()
{
    this->ui->admin->hide();
    this->ui->adminBtn->hide();
    this->ui->loginPanel->show();
    this->ui->loginPanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      displaySales
*******************************************************************************/

void MainWindow::displaySales()
{
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");
    this->ui->membersBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");

    this->ui->sales->raise();

    this->ui->salesFilterSelect->setCurrentIndex(0);
    this->ui->membersFilterSelect->setCurrentIndex(0);

    this->displaySalesByDate();
    this->displayMembersByDate();
}

/*******************************************************************************/



/****************************************************************************//**
 *      displayMembers
*******************************************************************************/

void MainWindow::displayMembers()
{
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->membersBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");

    int promoteCount = 0;
    int demoteCount = 0;

    this->ui->memberTable->setRowCount(0);

    QVector<MemberPurchaseData> purchaseDataList = this->database_manager.get_report_all_purchases_per_member();

    QVector<MemberPurchaseData> newPurchaseDataList;
    QVector<int> tempMemberVec;

    for (MemberPurchaseData& data : purchaseDataList)
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

    for (MemberPurchaseData& newListData : newPurchaseDataList)
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
    for (MemberPurchaseData& data : newPurchaseDataList)
    {
        this->ui->memberTable->insertRow(this->ui->memberTable ->rowCount());

        QTableWidgetItem  *name = new QTableWidgetItem;
        name->setData(Qt::EditRole, data.getName());
        name->setToolTip(data.getName());
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 0, name);

        QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
        membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
        membershipNumber->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 1, membershipNumber);

        QString membershipType = data.getMembershipType();
        QTableWidgetItem  *type = new QTableWidgetItem;
        type->setData(Qt::EditRole, membershipType);
        type->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 2, type);

        QTableWidgetItem  *date = new QTableWidgetItem;
        date->setData(Qt::EditRole, data.getExpirationDate());
        date->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 3, date);

        double totalSpentAmount = data.getTotalSpent() + (data.getTotalSpent() * TAX);
        QTableWidgetItem  *spent = new QTableWidgetItem;
        spent->setData(Qt::EditRole, "$" + QString::number(totalSpentAmount, 'f', 2));
        spent->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 4, spent);


        double totalSpentAmountWithoutTaxes = totalSpentAmount - (totalSpentAmount * TAX);
        QTableWidgetItem  *recommendedConversion = new QTableWidgetItem;

        if (membershipType == "Executive")
        {
            if (totalSpentAmountWithoutTaxes * 0.02 < 55)
            {
                recommendedConversion->setData(Qt::EditRole, "Executive 🠒 Regular");
                ++demoteCount;
            }
            else
            {
                recommendedConversion->setData(Qt::EditRole, "OK");
            }
        }
        else if (membershipType == "Regular")
        {
            if (totalSpentAmountWithoutTaxes * 0.02 > 55)
            {
                recommendedConversion->setData(Qt::EditRole, "Regular 🠒 Executive");
                ++promoteCount;
            }
            else
            {
                recommendedConversion->setData(Qt::EditRole, "OK");
            }
        }

        this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 5, recommendedConversion);

        this->database_manager.update_totalAmountSpent(QString::number(data.getMembershipNumber()), QString::number(totalSpentAmount));
        this->database_manager.update_rebateAmount(QString::number(data.getMembershipNumber()), QString::number(membershipType == "Executive" ? totalSpentAmountWithoutTaxes * 0.02 : 0));

        grandTotal += totalSpentAmount;
    }

    this->ui->memberTotalPromoDisplay->setText(QString::number(promoteCount));
    this->ui->memberTotalDemoDisplay->setText(QString::number(demoteCount));
    this->ui->memberTotalDisplay->setText("$" + QString::number(grandTotal, 'f', 2));

    this->ui->memberMainPanel->raise();
    this->ui->memberBackBtn->hide();

    this->ui->members->raise();
}
/*******************************************************************************/


/****************************************************************************//**
 *      displayAdmin
*******************************************************************************/

void MainWindow::displayAdmin()
{
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->membersBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");

    this->ui->manageInventoryTable->setRowCount(0);

    QVector<PurchaseData> purchaseDataList = this->database_manager.get_report_all_items();

    for (PurchaseData& data : purchaseDataList)
    {
        this->ui->manageInventoryTable->insertRow(this->ui->manageInventoryTable->rowCount());

        QTableWidgetItem  *itemName = new QTableWidgetItem;
        itemName->setData(Qt::EditRole, data.getProduct());
        itemName->setToolTip(data.getName());
        this->ui->manageInventoryTable->setItem(this->ui->manageInventoryTable->rowCount() - 1, 0, itemName);

        QTableWidgetItem  *itemPrice = new QTableWidgetItem;
        itemPrice->setData(Qt::EditRole, "$" + QString::number(data.getPrice(), 'f', 2));
        itemPrice->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->manageInventoryTable->setItem(this->ui->manageInventoryTable->rowCount() - 1, 1, itemPrice);
    }

    this->ui->manageMemberTable->setRowCount(0);

    QVector<MemberPurchaseData> purchaseDataList2 = this->database_manager.get_report_all_purchases_per_member();

    QVector<MemberPurchaseData> newPurchaseDataList;
    QVector<int> tempMemberVec;

    for (MemberPurchaseData& data : purchaseDataList2)
    {
       if (!tempMemberVec.contains(data.getMembershipNumber()))
       {
           MemberPurchaseData purchaseData;

           purchaseData.setName(data.getName());
           purchaseData.setMembershipNumber(data.getMembershipNumber());
           purchaseData.setMembershipType(data.getMembershipType());

           newPurchaseDataList.append(purchaseData);
           tempMemberVec.append(data.getMembershipNumber());
       }
    }

    for (MemberPurchaseData& data : newPurchaseDataList)
    {
        this->ui->manageMemberTable->insertRow(this->ui->manageMemberTable ->rowCount());

        QTableWidgetItem  *name = new QTableWidgetItem;
        name->setData(Qt::EditRole, data.getName());
        name->setToolTip(data.getName());
        this->ui->manageMemberTable->setItem(this->ui->manageMemberTable->rowCount() - 1, 0, name);

        QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
        membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
        membershipNumber->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->manageMemberTable->setItem(this->ui->manageMemberTable->rowCount() - 1, 1, membershipNumber);

        QString membershipType = data.getMembershipType();
        QTableWidgetItem  *type = new QTableWidgetItem;
        type->setData(Qt::EditRole, membershipType);
        type->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->manageMemberTable->setItem(this->ui->manageMemberTable->rowCount() - 1, 2, type);
    }

    this->ui->admin->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      displaySalesByDate
*******************************************************************************/

void MainWindow::displaySalesByDate()
{
    ui->salesTable->setSortingEnabled(false);
    ui->salesTable2->setSortingEnabled(false);

    this->ui->salesTable->setRowCount(0);

    QStringList memberOptions;

    memberOptions << "All members" << "Regular" << "Executive";

    int memberSelectionIndex = memberOptions.indexOf(this->ui->membersFilterSelect->currentText());

    QStringList dateOptions;

    dateOptions << "All purchases" << "04/01/2021" << "04/02/2021" << "04/03/2021" << "04/04/2021" << "04/05/2021" << "04/06/2021" << "04/07/2021";

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

            if (!tempProductVec.contains(data.getProduct()) && (memberSelectionIndex == 0 || (memberSelectionIndex != 0 && memberInfo.size() != 0 && memberOptions[memberSelectionIndex] == memberInfo.at(2))))
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
            quantity->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
            this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 1, quantity);

            QTableWidgetItem  *revenue = new QTableWidgetItem;
            revenue->setData(Qt::EditRole, data.getPrice() * data.getQuantity());
            revenue->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
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

            if (memberInfo.size() != 0)
            {
                if ((memberSelectionIndex == 0 && !tempMemberVec.contains(data.getMembershipNumber()))
                        || (memberSelectionIndex != 0 && !tempMemberVec.contains(data.getMembershipNumber()) && memberOptions[memberSelectionIndex] == memberInfo.at(2)))
                {
                    if (data.getProduct().toLower().indexOf(this->ui->salesSearchInput->text().toLower(), 0) != -1)
                    {
                        tempMemberVec.append(data.getMembershipNumber());
                    }
                }
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
                quantity->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 1, quantity);

                QTableWidgetItem  *revenue = new QTableWidgetItem;
                revenue->setData(Qt::EditRole, data.getPrice() * data.getQuantity());
                revenue->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 2, revenue);

                totalRevenue += data.getPrice() * data.getQuantity();
            }
        }
    }

    this->ui->salesRevDisplay->setText("$" + QString::number(totalRevenue + (totalRevenue * TAX), 'f', 2));

    ui->salesTable->setSortingEnabled(true);
    ui->salesTable2->setSortingEnabled(true);
}
/*******************************************************************************/



/****************************************************************************//**
 *      displayMembersByDate
*******************************************************************************/

void MainWindow::displayMembersByDate()
{
    ui->salesTable->setSortingEnabled(false);
    ui->salesTable2->setSortingEnabled(false);

    this->ui->salesTable2->setRowCount(0);

    QStringList dateOptions;

    dateOptions << "All purchases" << "04/01/2021" << "04/02/2021" << "04/03/2021" << "04/04/2021" << "04/05/2021" << "04/06/2021" << "04/07/2021";

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

    int regularShoppersCount = 0;
    int executiveShoppersCount = 0;

    QVector<int> tempMemberVec;
    for(PurchaseData& data : purchaseDataList)
    {
        QStringList memberInfo = this->database_manager.get_memberInfo(QString::number(data.getMembershipNumber()));

        if (memberInfo.size() == 0)
        {
            if (!tempMemberVec.contains(data.getMembershipNumber()))
            {
                this->ui->salesTable2->insertRow(this->ui->salesTable2 ->rowCount());

                this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 0, new QTableWidgetItem("Deleted"));

                QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
                membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
                membershipNumber->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 1, membershipNumber);

                tempMemberVec.append(data.getMembershipNumber());

                ++regularShoppersCount;
            }
        }
        else
        {
            if ((memberSelectionIndex == 0 && !tempMemberVec.contains(data.getMembershipNumber()))
                    || (memberSelectionIndex != 0 && !tempMemberVec.contains(data.getMembershipNumber()) && memberOptions[memberSelectionIndex] == memberInfo.at(2)))
            {

                this->ui->salesTable2->insertRow(this->ui->salesTable2 ->rowCount());

                this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 0, new QTableWidgetItem(memberInfo.at(0)));

                QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
                membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
                membershipNumber->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 1, membershipNumber);

                tempMemberVec.append(data.getMembershipNumber());

                if (memberInfo.at(2) == "Regular")
                    ++regularShoppersCount;
                else
                    ++executiveShoppersCount;
            }
        }
    }

    this->ui->regularShoppersDisplay->setText(QString::number(regularShoppersCount));
    this->ui->executiveShoppersDisplay->setText(QString::number(executiveShoppersCount));

    ui->salesTable->setSortingEnabled(true);
    ui->salesTable2->setSortingEnabled(true);
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_memberBackBtn_clicked
*******************************************************************************/

void MainWindow::on_memberBackBtn_clicked()
{
    this->ui->memberMainPanel->raise();
    this->ui->memberSearchLabel->show();
    this->ui->memberSearchInput->show();
    this->ui->memberBackBtn->hide();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_memberRebatesBtn_clicked
*******************************************************************************/

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
        membershipNumber->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->memberRebatesTable->setItem(this->ui->memberRebatesTable->rowCount() - 1, 1, membershipNumber);

        double totalSpentAmount = data.getTotalSpent();
        double totalSpentAmountWithoutTaxes = totalSpentAmount - (totalSpentAmount * TAX);

        QTableWidgetItem  *spentWithoutTaxes = new QTableWidgetItem;
        spentWithoutTaxes->setData(Qt::EditRole, "$" + QString::number(totalSpentAmountWithoutTaxes, 'f', 2));
        spentWithoutTaxes->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->memberRebatesTable->setItem(this->ui->memberRebatesTable->rowCount() - 1, 2, spentWithoutTaxes);

        QTableWidgetItem  *spent = new QTableWidgetItem;
        spent->setData(Qt::EditRole, "$" + QString::number(totalSpentAmount, 'f', 2));
        spent->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->memberRebatesTable->setItem(this->ui->memberRebatesTable->rowCount() - 1, 3, spent);

        QTableWidgetItem  *rebate = new QTableWidgetItem;
        rebate->setData(Qt::EditRole, "$" + QString::number(data.getRebateAmount(), 'f', 2));
        rebate->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ui->memberRebatesTable->setItem(this->ui->memberRebatesTable->rowCount() - 1, 4, rebate);
    }

    this->ui->memberRebatesPanel->raise();
    this->ui->memberSearchLabel->hide();
    this->ui->memberSearchInput->hide();
    this->ui->memberBackBtn->show();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_memberExpirationBtn_clicked
*******************************************************************************/

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
/*******************************************************************************/



/****************************************************************************//**
 *      on_expirationMonthSelect_currentIndexChanged
*******************************************************************************/

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
            costToRenew->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
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
            costToRenew->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
            this->ui->expiredExecutiveTable->setItem(this->ui->expiredExecutiveTable->rowCount() - 1, 1, costToRenew);
        }
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_salesSearchInput_textChanged
*******************************************************************************/

void MainWindow::on_salesSearchInput_textChanged()
{
    if (this->ui->salesSearchInput->text() == "")
    {
        displaySalesByDate();
        displayMembersByDate();
    }
    else
    {
        ui->salesTable->setSortingEnabled(false);
        ui->salesTable2->setSortingEnabled(false);

        this->ui->salesTable->setRowCount(0);

        QStringList memberOptions;

        memberOptions << "All members" << "Regular" << "Executive" << "Deleted";

        int memberSelectionIndex = memberOptions.indexOf(this->ui->membersFilterSelect->currentText());

        QStringList dateOptions;

        dateOptions << "All purchases" << "04/01/2021" << "04/02/2021" << "04/03/2021" << "04/04/2021" << "04/05/2021" << "04/06/2021" << "04/07/2021";

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

                if (!tempProductVec.contains(data.getProduct()) && (memberSelectionIndex == 0 || (memberSelectionIndex != 0 && memberInfo.size() != 0 && memberOptions[memberSelectionIndex] == memberInfo.at(2))))
                {
                    if (data.getProduct().toLower().indexOf(this->ui->salesSearchInput->text().toLower(), 0) != -1
                            || QString::number(data.getMembershipNumber()).toLower().indexOf(this->ui->salesSearchInput->text().toLower(), 0) != -1)
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
                quantity->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 1, quantity);

                QTableWidgetItem  *revenue = new QTableWidgetItem;
                revenue->setData(Qt::EditRole, data.getPrice() * data.getQuantity());
                revenue->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
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

                if (memberInfo.size() != 0)
                {
                    if ((memberSelectionIndex == 0 && !tempMemberVec.contains(data.getMembershipNumber()))
                            || (memberSelectionIndex != 0 && !tempMemberVec.contains(data.getMembershipNumber()) && memberOptions[memberSelectionIndex] == memberInfo.at(2)))
                    {
                        if (data.getProduct().toLower().indexOf(this->ui->salesSearchInput->text().toLower(), 0) != -1)
                        {
                            tempMemberVec.append(data.getMembershipNumber());
                        }
                    }
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
                    quantity->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                    this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 1, quantity);

                    QTableWidgetItem  *revenue = new QTableWidgetItem;
                    revenue->setData(Qt::EditRole, data.getPrice() * data.getQuantity());
                    revenue->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                    this->ui->salesTable->setItem(this->ui->salesTable->rowCount() - 1, 2, revenue);

                    totalRevenue += data.getPrice() * data.getQuantity();
                }
            }
        }

        this->ui->salesRevDisplay->setText("$" + QString::number(totalRevenue + (totalRevenue * TAX), 'f', 2));

        this->ui->salesTable2->setRowCount(0);

        QVector<PurchaseData> purchaseDataList2;

        int dataSelectionIndex = dateOptions.indexOf(this->ui->salesFilterSelect->currentText());
        if (dataSelectionIndex > 0 && dataSelectionIndex < dateOptions.size())
        {
            QDate date = QDate(2021, 4, dateOptions.indexOf(this->ui->salesFilterSelect->currentText()));

            purchaseDataList2 = this->database_manager.get_report_purchases_by_date(date);
        }
        else
        {
            purchaseDataList2 = this->database_manager.get_report_all_purchases();
        }

        int regularShoppersCount = 0;
        int executiveShoppersCount = 0;

        QVector<int> tempMemberVec;
        for(PurchaseData& data : purchaseDataList2)
        {
            QStringList memberInfo = this->database_manager.get_memberInfo(QString::number(data.getMembershipNumber()));

            if (memberInfo.size() == 0)
            {
                if (!tempMemberVec.contains(data.getMembershipNumber()))
                {
                    this->ui->salesTable2->insertRow(this->ui->salesTable2 ->rowCount());

                    this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 0, new QTableWidgetItem("Deleted"));

                    QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
                    membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
                    membershipNumber->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                    this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 1, membershipNumber);

                    tempMemberVec.append(data.getMembershipNumber());

                    ++regularShoppersCount;
                }
            }
            else
            {
                if ((memberSelectionIndex == 0 && !tempMemberVec.contains(data.getMembershipNumber()))
                        || (memberSelectionIndex != 0 && !tempMemberVec.contains(data.getMembershipNumber()) && memberOptions[memberSelectionIndex] == memberInfo.at(2)))
                {

                    this->ui->salesTable2->insertRow(this->ui->salesTable2 ->rowCount());

                    this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 0, new QTableWidgetItem(memberInfo.at(0)));

                    QTableWidgetItem  *membershipNumber = new QTableWidgetItem;
                    membershipNumber->setData(Qt::EditRole, data.getMembershipNumber());
                    membershipNumber->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
                    this->ui->salesTable2->setItem(this->ui->salesTable2->rowCount() - 1, 1, membershipNumber);

                    tempMemberVec.append(data.getMembershipNumber());

                    if (memberInfo.at(2) == "Regular")
                        ++regularShoppersCount;
                    else
                        ++executiveShoppersCount;
                }
            }
        }

        this->ui->regularShoppersDisplay->setText(QString::number(regularShoppersCount));
        this->ui->executiveShoppersDisplay->setText(QString::number(executiveShoppersCount));

        ui->salesTable->setSortingEnabled(true);
        ui->salesTable2->setSortingEnabled(true);
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_memberSearchInput_textChanged
*******************************************************************************/

void MainWindow::on_memberSearchInput_textChanged()
{
    if (this->ui->memberSearchInput->text() == "")
    {
        displayMembers();
    }
    else
    {
        int promoteCount = 0;
        int demoteCount = 0;

        this->ui->memberTable->setRowCount(0);

        QVector<MemberPurchaseData> purchaseDataList = this->database_manager.get_report_all_purchases_per_member();

        QVector<MemberPurchaseData> newPurchaseDataList;
        QVector<int> tempMemberVec;

        for(MemberPurchaseData& data : purchaseDataList)
        {
           if (!tempMemberVec.contains(data.getMembershipNumber()))
           {
               if (data.getName().toLower().indexOf(this->ui->memberSearchInput->text().toLower(), 0) != -1
                       || QString::number(data.getMembershipNumber()).toLower().indexOf(this->ui->memberSearchInput->text().toLower(), 0) != -1)
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
            membershipNumber->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
            this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 1, membershipNumber);

            QString membershipType = data.getMembershipType();
            QTableWidgetItem  *type = new QTableWidgetItem;
            type->setData(Qt::EditRole, membershipType);
            type->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
            this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 2, type);

            QTableWidgetItem  *date = new QTableWidgetItem;
            date->setData(Qt::EditRole, data.getExpirationDate());
            date->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
            this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 3, date);

            double totalSpentAmount = data.getTotalSpent() + (data.getTotalSpent() * TAX);
            QTableWidgetItem  *spent = new QTableWidgetItem;
            spent->setData(Qt::EditRole, "$" + QString::number(totalSpentAmount, 'f', 2));
            spent->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
            this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 4, spent);

            double totalSpentAmountWithoutTaxes = totalSpentAmount - (totalSpentAmount * TAX);
            QTableWidgetItem  *recommendedConversion = new QTableWidgetItem;

            if (membershipType == "Executive")
            {
                if (totalSpentAmountWithoutTaxes * 0.02 < 55)
                {
                    recommendedConversion->setData(Qt::EditRole, "Executive 🠒 Regular");
                    ++demoteCount;
                }
                else
                {
                    recommendedConversion->setData(Qt::EditRole, "OK");
                }
            }
            else if (membershipType == "Regular")
            {
                if (totalSpentAmountWithoutTaxes * 0.02 > 55)
                {
                    recommendedConversion->setData(Qt::EditRole, "Regular 🠒 Executive");
                    ++promoteCount;
                }
                else
                {
                    recommendedConversion->setData(Qt::EditRole, "OK");
                }
            }

            this->ui->memberTable->setItem(this->ui->memberTable->rowCount() - 1, 5, recommendedConversion);

            grandTotal += totalSpentAmount;
        }

        this->ui->memberTotalPromoDisplay->setText(QString::number(promoteCount));
        this->ui->memberTotalDemoDisplay->setText(QString::number(demoteCount));
        this->ui->memberTotalDisplay->setText("$" + QString::number(grandTotal, 'f', 2));
    }
}

/*******************************************************************************/



/****************************************************************************//**
 *      on_manageInventoryBtn_clicked
*******************************************************************************/

void MainWindow::on_manageInventoryBtn_clicked()
{
    this->ui->manageInventoryPanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_manageMemberBtn_clicked
*******************************************************************************/

void MainWindow::on_manageMemberBtn_clicked()
{
    this->ui->manageMemberPanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_manageAddItemBtn_clicked
*******************************************************************************/

void MainWindow::on_manageAddItemBtn_clicked()
{
    this->ui->addItemPanel->show();
    this->ui->delItemPanel->hide();
    this->ui->upItemPanel->hide();
    this->ui->addMemPanel->hide();
    this->ui->delMemPanel->hide();
    this->ui->addPurchasePanel->hide();

    this->ui->addItemPanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_addItemOkBtn_clicked
*******************************************************************************/

void MainWindow::on_addItemOkBtn_clicked()
{
    QString item_name = this->ui->addItemNameInput->text();
    QString item_price = this->ui->addItemPriceInput->text();

    bool inputValid = true;
    int countDecimal = 0;

    QMessageBox errorMessageBox;

    // No field can be left empty
    if (item_name.isEmpty() || item_price.isEmpty())
    {
        errorMessageBox.setText("INVALID INPUT:\nALL fields must be entered.");
        errorMessageBox.exec();
        inputValid = false;
    }

    // item_price can only contain digits, commas, and one period as decimal.
    for (int i = 0; i < item_price.size(); i++)
    {
        // Check if only digits, commas, and periods present
        if ( !(item_price[i].isDigit() || item_price[i] == "," || item_price[i] == ".") )
        {
            errorMessageBox.setText("INVALID INPUT:\nPrice for item can only contain numbers, commas (optional), and one decimal");
            inputValid = false;
            errorMessageBox.exec();
            break;
        }

        if (item_price[i] == ".")
        {
            countDecimal++;
        }

        if (countDecimal > 1)
        {
            errorMessageBox.setText("INVALID INPUT:\nPrice can only contain one decimal.");
            inputValid = false;
            errorMessageBox.exec();
            break;
        }
    }

    if (inputValid)
    {
        this->database_manager.add_item(item_name, item_price);
    }

    this->ui->addItemNameInput->clear();
    this->ui->addItemPriceInput->clear();

    this->ui->addItemPanel->hide();
    this->displayAdmin();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_addItemCancelBtn_clicked
*******************************************************************************/

void MainWindow::on_addItemCancelBtn_clicked()
{
    this->ui->addItemNameInput->clear();
    this->ui->addItemPriceInput->clear();

    this->ui->addItemPanel->hide();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_manageDelItemBtn_clicked
*******************************************************************************/

void MainWindow::on_manageDelItemBtn_clicked()
{
    this->ui->addItemPanel->hide();
    this->ui->delItemPanel->show();
    this->ui->upItemPanel->hide();
    this->ui->addMemPanel->hide();
    this->ui->delMemPanel->hide();
    this->ui->addPurchasePanel->hide();

    this->ui->delItemPanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_delItemOkBtn_clicked
*******************************************************************************/

void MainWindow::on_delItemOkBtn_clicked()
{
    QString item_name = this->ui->delItemNameInput->text();

    QMessageBox errorMessageBox;

    if (this->database_manager.check_item_existance(item_name))
    {
        this->database_manager.delete_item(item_name);
    }
    else
    {
        errorMessageBox.setText("Item does not exist. Check name and id again!\n");
        errorMessageBox.exec();
    }

    this->ui->delItemNameInput->clear();

    this->ui->delItemPanel->hide();
    this->displayAdmin();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_delItemCancelBtn_clicked
*******************************************************************************/

void MainWindow::on_delItemCancelBtn_clicked()
{
    this->ui->delItemNameInput->clear();

    this->ui->delItemPanel->hide();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_manageUpItemBtn_clicked
*******************************************************************************/

void MainWindow::on_manageUpItemBtn_clicked()
{
    this->ui->addItemPanel->hide();
    this->ui->delItemPanel->hide();
    this->ui->upItemPanel->show();
    this->ui->addMemPanel->hide();
    this->ui->delMemPanel->hide();
    this->ui->addPurchasePanel->hide();

    this->ui->upItemPanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_upItemOkBtn_clicked
*******************************************************************************/

void MainWindow::on_upItemOkBtn_clicked()
{
    QString item_name = this->ui->upItemNameInput->text();
    QString item_new_price = this->ui->upItemPriceInput->text();

    QMessageBox errorMessageBox;

    if (this->database_manager.check_item_existance(item_name))
    {
        this->database_manager.update_item(item_name, item_new_price);
    }
    else
    {
        errorMessageBox.setText("Item does not exist. Check item name again!\n");
        errorMessageBox.exec();
    }

    this->ui->upItemNameInput->clear();
    this->ui->upItemPriceInput->clear();

    this->ui->upItemPanel->hide();
    this->displayAdmin();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_upItemCancelBtn_clicked
*******************************************************************************/

void MainWindow::on_upItemCancelBtn_clicked()
{
    this->ui->upItemNameInput->clear();
    this->ui->upItemPriceInput->clear();

    this->ui->upItemPanel->hide();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_manageAddMemBtn_clicked
*******************************************************************************/

void MainWindow::on_manageAddMemBtn_clicked()
{
    this->ui->addItemPanel->hide();
    this->ui->delItemPanel->hide();
    this->ui->upItemPanel->hide();
    this->ui->addMemPanel->show();
    this->ui->delMemPanel->hide();
    this->ui->addPurchasePanel->hide();

    this->ui->addMemPanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_addMemOkBtn_clicked
*******************************************************************************/

void MainWindow::on_addMemOkBtn_clicked()
{
    QString member_name;
    QString member_type;

    bool regular_checked;
    bool executive_checked;

    QMessageBox errorMessageBox;

    // Get member name from ui. If left empty, tell user.
    member_name = this->ui->addMemNameInput->text();
    if (member_name.isEmpty() )
    {
        qDebug() << "Name left empty.\n";
        errorMessageBox.setText("Enter name");
        errorMessageBox.exec();
        return;
    }

    // Find state of the checkboxes
    regular_checked = this->ui->addMemTypeSelect->currentText() == "Regular";
    executive_checked = this->ui->addMemTypeSelect->currentText() == "Executive";

    // Check if check box for membership type is selected. If it is, assign
    // type to member_type variable.
    if ( regular_checked && executive_checked)
    {
        qDebug() << "Select ONE member type.\n";
        errorMessageBox.setText("Select ONE membership type.\n");
        errorMessageBox.exec();
        return;
    }
    else if (regular_checked)
    {
        member_type = "Regular";
    }
    else if (executive_checked)
    {
        member_type = "Executive";
    }
    else
    {
        qDebug() << "Select a member type.\n";
        errorMessageBox.setText("Select a membership type.\n");
        errorMessageBox.exec();
        return;
    }

    // After checking inputs, add member.
    this->database_manager.add_member(member_name, member_type);

    this->ui->addMemNameInput->clear();

    this->ui->addMemPanel->hide();
    this->displayAdmin();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_addMemCancelBtn_clicked
*******************************************************************************/

void MainWindow::on_addMemCancelBtn_clicked()
{
    this->ui->addMemNameInput->clear();

    this->ui->addMemPanel->hide();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_manageDelMemBtn_clicked
*******************************************************************************/

void MainWindow::on_manageDelMemBtn_clicked()
{
    this->ui->addItemPanel->hide();
    this->ui->delItemPanel->hide();
    this->ui->upItemPanel->hide();
    this->ui->addMemPanel->hide();
    this->ui->delMemPanel->show();
    this->ui->addPurchasePanel->hide();

    this->ui->delMemPanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_delMemOkBtn_clicked
*******************************************************************************/

void MainWindow::on_delMemOkBtn_clicked()
{
    QString member_id;
    QString member_name;

    QMessageBox errorMessageBox;

    // Get member's name and id from ui.
    member_id = this->ui->delMemIdInput->text();
    member_name = this->ui->delMemNameInput->text();

    // Check if member exists
    // If member does not exist in database, prompt error.
    if (!this->database_manager.check_member_existance(member_name, member_id))
    {
        errorMessageBox.setText("Member does not exist. Check name and id again!\n");
        errorMessageBox.exec();
        return;
    }

    this->database_manager.delete_member(member_name, member_id);

    this->ui->delMemIdInput->clear();
    this->ui->delMemNameInput->clear();

    this->ui->delMemPanel->hide();
    this->displayAdmin();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_delMemCancelBtn_clicked
 * ____________________________________________________________________________

*******************************************************************************/

void MainWindow::on_delMemCancelBtn_clicked()
{
    this->ui->delMemIdInput->clear();
    this->ui->delMemNameInput->clear();

    this->ui->delMemPanel->hide();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_manageAddPurchaseBtn_clicked
*******************************************************************************/

void MainWindow::on_manageAddPurchaseBtn_clicked()
{
    this->ui->addItemPanel->hide();
    this->ui->delItemPanel->hide();
    this->ui->upItemPanel->hide();
    this->ui->addMemPanel->hide();
    this->ui->delMemPanel->hide();
    this->ui->addPurchasePanel->show();

    this->ui->addPurchasePanel->raise();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_addPurchaseOkBtn_clicked
*******************************************************************************/

void MainWindow::on_addPurchaseOkBtn_clicked()
{
    QMessageBox messageBox;

    QString memberID;
    QString product_name;
    QString product_price;
    QString quantity;
    QString date;

    // Get purchase data from UI
    memberID = this->ui->addPurMemIdInput->text();
    product_name = this->ui->addPurNameInput->text();
    product_price = this->ui->addPurPriceInput->text();
    quantity = this->ui->addPurQuantInput->text();
    date = this->ui->addPurDateSelect->currentText();

    // Check if any lineEdits left empty. check_lineEdits returns true if lineEdit found to be empty.
    if (checkLineEdits(memberID, product_name, product_price, quantity, date))
    {
        return;
    }

    // Check if member exists. You shouldn't be able to add purchase for a non existant member.
    if (this->database_manager.check_member_existance(memberID) == false)
    {
        messageBox.setText("Cannot add purchase for a member that does not exist. \nCheck member ID and try again!\n");
        messageBox.exec();

        return;
    }

    this->database_manager.add_member_purchase(memberID, product_name, product_price, quantity, date);

    this->ui->addPurMemIdInput->clear();
    this->ui->addPurNameInput->clear();
    this->ui->addPurPriceInput->clear();
    this->ui->addPurQuantInput->clear();

    this->ui->addPurchasePanel->hide();
    this->displayAdmin();
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_addPurchaseCancelBtn_clicked
*******************************************************************************/

void MainWindow::on_addPurchaseCancelBtn_clicked()
{
    this->ui->addPurMemIdInput->clear();
    this->ui->addPurNameInput->clear();
    this->ui->addPurPriceInput->clear();
    this->ui->addPurQuantInput->clear();

    this->ui->addPurchasePanel->hide();
}
/*******************************************************************************/



/****************************************************************************//**
 *      checkLineEdits
 * ____________________________________________________________________________
 * Function checks the inputs of the line edits. The line edits checks the inputs
 * for the add purchase functionality.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param memberID : QString representing member's member ID
 *      @param product_name : QString representing product's name.
 *      @param product_price : QString representing product's price.
 *      @param quantity : QString representing quantity bought
 *      @param date : QString representing data of purchase.
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

// Returns true if errors found.
bool MainWindow::checkLineEdits(QString& memberID, QString& product_name, QString& product_price, QString& quantity,  QString& date) const
{
    QString errorMessageText;
    bool errorFound = false;
    QMessageBox msg;

    // Check if memberID empty.
    if (memberID.isEmpty() || isWhiteSpace(memberID))
    {
        errorMessageText.append(" - Enter Member ID\n");
        errorFound = true;
    }

    // Check if product_name empty.
    if (product_name.isEmpty() || isWhiteSpace(product_name))
    {
        errorMessageText.append(" - Enter Product Name\n");
        errorFound = true;
    }
    // Check if product_price empty.
    if (product_price.isEmpty() || isWhiteSpace(product_price))
    {
        errorMessageText.append(" - Enter Product Price\n");
        errorFound = true;
    }
    // Check if quantity empty.
    if (quantity.isEmpty() || isWhiteSpace(quantity))
    {
        errorMessageText.append(" - Enter Quanity\n");
        errorFound = true;
    }
    // Check if date empty.
    if (date.isEmpty() || isWhiteSpace(date))
    {
        errorMessageText.append(" - Enter Date of Purchase\n");
        errorFound = true;
    }

    if (errorFound)
    {
        msg.setText(errorMessageText);
        msg.exec();
        return true;
    }

    return false;
}
/*******************************************************************************/



/****************************************************************************//**
 *      isWhiteSpace
 * ____________________________________________________________________________
 * Function checks if a string contains only white spaces.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param str : QString that needs to be checked.
 *
 * \b OUTPUT:
 *      @return  QRegExp("\\s*").exactMatch(str) :
*******************************************************************************/

bool MainWindow::isWhiteSpace(const QString & str) const
{
  return QRegExp("\\s*").exactMatch(str);
}
/*******************************************************************************/


