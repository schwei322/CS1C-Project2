#include "managemember.h"
#include "ui_managemember.h"

ManageMember::ManageMember(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageMember)
{
    ui->setupUi(this);
}

ManageMember::~ManageMember()
{
    delete ui;
}
