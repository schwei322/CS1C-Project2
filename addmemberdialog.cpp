#include "addmemberdialog.h"
#include "ui_addmemberdialog.h"

/****************************************************************************//**
 *      Constructor
 * ____________________________________________________________________________
*******************************************************************************/

AddMemberDialog::AddMemberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMemberDialog)
{
    ui->setupUi(this);
}
/*******************************************************************************/



/****************************************************************************//**
 *      Decontructor
 * ____________________________________________________________________________
*******************************************************************************/

AddMemberDialog::~AddMemberDialog()
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

void AddMemberDialog::on_btn_OK_clicked()
{
    QString member_name;
    QString member_type;
    bool regular_checked;
    bool executive_checked;
    QMessageBox message;
    Database_manager db;

    // Get member name from ui. If left empty, tell user.
    member_name = ui->lineEdit_memberName->text();
    if (member_name.isEmpty() )
    {
        qDebug() << "Name left empty.\n";
        message.setText("Enter name");
        message.exec();
        return;
    }

    // Find state of the checkboxes
    regular_checked = ui->checkBox_regularMember->checkState();
    executive_checked = ui->checkBox_executiveMember->checkState();

    // Check if check box for membership type is selected. If it is, assign
    // type to member_type variable.
    if ( regular_checked && executive_checked)
    {
        qDebug() << "Select ONE member type.\n";
        message.setText("Select ONE membership type.\n");
        message.exec();
        return;
    }
    else if (regular_checked)
    {
        member_type = "Regular";
    }
    else if (executive_checked)
    {
        member_type = "Executive";
    }
    else
    {
        qDebug() << "Select a member type.\n";
        message.setText("Select a membership type.\n");
        message.exec();
        return;
    }

    // After checking inputs, add member.
    db.add_member(member_name, member_type);
    QWidget::close();
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

void AddMemberDialog::on_btn_cancel_clicked()
{
    QWidget::close();
}
/*******************************************************************************/



/****************************************************************************//**
 *      ~~~~~~~~~~~~
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



