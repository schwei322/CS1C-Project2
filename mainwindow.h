#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>

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

private slots:
    //void on_dateEdit_editingFinished();

    //void on_sales_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    DatabaseManager database_manager;

};
#endif // MAINWINDOW_H
