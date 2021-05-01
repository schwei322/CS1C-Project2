#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete this->memberMangeWindow;
    delete ui;
}

void Admin::on_pushButton_clicked()
{
    this->memberMangeWindow = new ManageMem();
    this->memberMangeWindow->show();
}

void Admin::on_pushButton_2_clicked()
{
    this->manageItemWindow = new ManageItem();
    this->manageItemWindow->show();
}
