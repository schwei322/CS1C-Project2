#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef QT_DEBUG
    bool debugMode = true;
#else
    bool debugMode = false;
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->salesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
