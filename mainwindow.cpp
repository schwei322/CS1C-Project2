#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->displayHome();

    ui->loginPanel->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userAuthenticate()
{
    if (this->ui->usernameInput->text() == "admin" && this->ui->passwordInput->text() == "password")
    {
        this->ui->loginPanel->hide();
    }
}

void MainWindow::displayHome()
{
    this->ui->homeBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");
    this->ui->manageBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");

    this->ui->home->raise();
}

void MainWindow::displayManage()
{
    this->ui->homeBtn->setStyleSheet("border: none; background-color: rgb(0, 76, 76); color: rgb(178, 216, 216);");
    this->ui->manageBtn->setStyleSheet("border: none; background-color: rgb(0, 128, 128); color: rgb(178, 216, 216);");

    this->ui->manage->raise();
}
