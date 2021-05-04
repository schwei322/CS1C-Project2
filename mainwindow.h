#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "additemdialog.h"
#include "deleteitemdialog.h"
#include "addmemberdialog.h"
#include "deletememberdialog.h"
#include "updateitemdialog.h"

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

private slots:
    void on_adminAddItemBtn_clicked();

    void on_adminDelItemBtn_clicked();

    void on_adminAddMemBtn_clicked();

    void on_adminDelMemBtn_clicked();

    void on_adminLoadInventoryBtn_clicked();

    void on_btn_adminUpdateItemPrice_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
