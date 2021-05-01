#include "deletememberdialog.h"
#include "ui_deletememberdialog.h"

DeleteMemberDialog::DeleteMemberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteMemberDialog)
{
    ui->setupUi(this);
}

DeleteMemberDialog::~DeleteMemberDialog()
{
    delete ui;
}
