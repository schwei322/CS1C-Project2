#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->displayHome();

    ui->adminLogin->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userAuthenticate()
{
    if (this->ui->usernameInput->text() == "admin" && this->ui->passwordInput->text() == "admin")
    {
        this->ui->adminBtn->show();
        this->ui->loginPanel->hide();
    }
    else if (this->ui->usernameInput->text() == "manager" && this->ui->passwordInput->text() == "manager")
    {
        this->ui->loginPanel->hide();
    }
}

void MainWindow::displayHome()
{
    this->ui->homeBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");

    this->ui->homePanel->raise();
}

void MainWindow::displaySales()
{
    this->ui->homeBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");

    this->ui->salesPanel->raise();
}

void MainWindow::displayAdmin()
{
    this->ui->homeBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->salesBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->adminBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");

    this->ui->loginPanel->raise();
}
void MainWindow::on_pushButton_clicked()
{
    this->adminWindow = new Admin();
    this->adminWindow->show();
}
