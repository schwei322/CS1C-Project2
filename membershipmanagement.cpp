#include "membershipmanagement.h"
#include "ui_membershipmanagement.h"
#include "admin.h"

membershipManagement::membershipManagement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::membershipManagement)
{
    ui->setupUi(this);
}

membershipManagement::~membershipManagement()
{
    delete ui;
}
