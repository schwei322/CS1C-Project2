/**
 *  @file mainwindow.h
 *  @brief contain slots that handle the GUI
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QRegExp>
#include "database_manager.h"
#include "purchasedata.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void userLogin();
    void userLogout();
    void displaySales();
    void displayMembers();
    void displayAdmin();

    void displaySalesByDate();
    void displayMembersByDate();

    /**
     * @brief checkLineEdits
     * @param memberID         identifies member
     * @param product_name     identifies product
     * @param product_price    product cost
     * @param quantity         amount of the product
     * @param date             identifies the purchase date, expiration date.
     */
    bool checkLineEdits(QString& memberID, QString& product_name, QString& product_price, QString& quantity,  QString& date) const;
    bool isWhiteSpace(const QString & str) const;

private slots:
    void on_memberBackBtn_clicked();
    void on_memberRebatesBtn_clicked();
    void on_memberExpirationBtn_clicked();
    void on_expirationMonthSelect_currentIndexChanged();
    void on_salesSearchInput_textChanged();
    void on_memberSearchInput_textChanged();

    void on_manageInventoryBtn_clicked();
    void on_manageMemberBtn_clicked();

    void on_manageAddItemBtn_clicked();
    void on_addItemOkBtn_clicked();
    void on_addItemCancelBtn_clicked();

    void on_manageDelItemBtn_clicked();
    void on_delItemOkBtn_clicked();
    void on_delItemCancelBtn_clicked();

    void on_manageUpItemBtn_clicked();
    void on_upItemOkBtn_clicked();
    void on_upItemCancelBtn_clicked();

    void on_manageAddMemBtn_clicked();
    void on_addMemOkBtn_clicked();
    void on_addMemCancelBtn_clicked();

    void on_manageDelMemBtn_clicked();
    void on_delMemOkBtn_clicked();
    void on_delMemCancelBtn_clicked();

    void on_manageAddPurchaseBtn_clicked();
    void on_addPurchaseOkBtn_clicked();
    void on_addPurchaseCancelBtn_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseManager database_manager;

};
#endif // MAINWINDOW_H
