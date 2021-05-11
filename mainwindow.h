#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>

#include "database_manager.h"
#include "purchasedata.h"
#include "expmonth.h"

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

private slots:
    void on_memberBackBtn_clicked();
    void on_memberRebatesBtn_clicked();
    void on_memberPurchasesBtn_clicked();
    void on_memberExpirationBtn_clicked();
    void on_expirationMonthSelect_currentIndexChanged();

    void on_memberExpirationBtn_clicked();

    void on_salesSearchInput_editingFinished();

private:
    Ui::MainWindow *ui;
    DatabaseManager database_manager;
    expMonth *expirationMonth;

};
#endif // MAINWINDOW_H
