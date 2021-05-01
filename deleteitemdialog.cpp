#include "deleteitemdialog.h"
#include "ui_deleteitemdialog.h"

DeleteItemDialog::DeleteItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteItemDialog)
{
    ui->setupUi(this);
}

DeleteItemDialog::~DeleteItemDialog()
{
    delete ui;
}
