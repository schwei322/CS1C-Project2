#include "addmemberdialog.h"
#include "ui_addmemberdialog.h"

AddMemberDialog::AddMemberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMemberDialog)
{
    ui->setupUi(this);
}

AddMemberDialog::~AddMemberDialog()
{
    delete ui;
}
