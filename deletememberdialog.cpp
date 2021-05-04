#include "deletememberdialog.h"
#include "ui_deletememberdialog.h"

/****************************************************************************//**
 *      Constructor
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

DeleteMemberDialog::DeleteMemberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteMemberDialog)
{
    ui->setupUi(this);
}
/*******************************************************************************/



/****************************************************************************//**
 *      Deconstructor
 * ____________________________________________________________________________
*******************************************************************************/

DeleteMemberDialog::~DeleteMemberDialog()
{
    delete ui;
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_btn_OK_clicked
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void DeleteMemberDialog::on_btn_OK_clicked()
{
    QString member_id;
    QString member_name;
    Database_manager db;
    QMessageBox errorMessage;

    // Get member's name and id from ui.
    member_id = ui->lineEdit_memID->text();
    member_name = ui->lineEdit_memName->text();

    // Check if member exists


    bool buff = db.check_member_existance(member_name, member_id);
    qDebug() << "HERE: " << buff;

    // If member does not exist in database, prompt error.
    if (db.check_member_existance(member_name, member_id))
    {
        db.delete_member(member_name, member_id);
        QWidget::close();
        return;
    }
    else
    {
        errorMessage.setText("Member does not exist. Check name and id.\n");
        errorMessage.exec();
        return;
    }
}
/*******************************************************************************/



/****************************************************************************//**
 *      on_btn_cancel_clicked
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

void DeleteMemberDialog::on_btn_cancel_clicked()
{
    QWidget::close();
}
/*******************************************************************************/



/****************************************************************************//**
 *      ~~~~~~~~~~
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

/*******************************************************************************/




