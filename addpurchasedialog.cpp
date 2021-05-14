#include "addpurchasedialog.h"
#include "ui_addpurchasedialog.h"

/****************************************************************************//**
 *      AddPurchaseDialog
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

AddPurchaseDialog::AddPurchaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPurchaseDialog)
{
    ui->setupUi(this);
}
/*******************************************************************************/



/****************************************************************************//**
 *      AddPurchaseDialog
 * ____________________________________________________________________________
*******************************************************************************/

AddPurchaseDialog::~AddPurchaseDialog()
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

void AddPurchaseDialog::on_btn_OK_clicked()
{
    Database_manager db;
    QMessageBox nonexistant_member_error_dialog;
    QMessageBox msg;
    QString memberID;
    QString product_name;
    QString product_price;
    QString quantity;
    QString date;

    // Get purchase data from UI
    memberID = ui->lineEdit_memberID->text();
    product_name = ui->lineEdit_productName->text();
    product_price = ui->lineEdit_productPrice->text();
    quantity = ui->lineEdit_quantityBought->text();
    date = ui->lineEdit_dateOfPurchase->text();\

    // Check if any lineEdits left empty. check_lineEdits returns true if lineEdit found to be empty.
    if (check_lineEdits(memberID, product_name, product_price, quantity, date))
    {
        return;
    }

    // Check if member exists. You shouldn't be able to add purchase for a non existant member.
    if (db.check_member_existance(memberID) == false)
    {
        qDebug() << "Purchase did not insert. Reason: Member does not exist.";
        nonexistant_member_error_dialog.setText("Cannot add purchase for a member that does not exist. \nCheck member ID and try again.\n");
        nonexistant_member_error_dialog.exec();
        return;
    }

    db.add_member_purchase(memberID, product_name, product_price, quantity, date);

    msg.setText("Purchase Inserted Sucessfully.\n");
    msg.exec();

    QDialog::close();
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

void AddPurchaseDialog::on_btn_cancel_clicked()
{
    QDialog::close();
}
/*******************************************************************************/



/****************************************************************************//**
 *      check_lineEdits
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

// Returns true if errors found.
bool AddPurchaseDialog::check_lineEdits(QString& memberID, QString& product_name, QString& product_price, QString& quantity,  QString& date) const
{
    QString errorMessageText;
    bool errorFound = false;
    QMessageBox msg;

    // Check if memberID empty.
    if (memberID.isEmpty() || isWhiteSpace(memberID))
    {
        errorMessageText.append(" - Enter Member ID\n");
        errorFound = true;
    }

    // Check if product_name empty.
    if (product_name.isEmpty() || isWhiteSpace(product_name))
    {
        errorMessageText.append(" - Enter Product Name\n");
        errorFound = true;
    }
    // Check if product_price empty.
    if (product_price.isEmpty() || isWhiteSpace(product_price))
    {
        errorMessageText.append(" - Enter Product Price\n");
        errorFound = true;
    }
    // Check if quantity empty.
    if (quantity.isEmpty() || isWhiteSpace(quantity))
    {
        errorMessageText.append(" - Enter Quanity\n");
        errorFound = true;
    }
    // Check if date empty.
    if (date.isEmpty() || isWhiteSpace(date))
    {
        errorMessageText.append(" - Enter Date of Purchase\n");
        errorFound = true;
    }

    if (errorFound)
    {
        msg.setText(errorMessageText);
        msg.exec();
        return true;
    }

    return false;
}
/*******************************************************************************/



/****************************************************************************//**
 *      isWhiteSpace
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

bool AddPurchaseDialog::isWhiteSpace(const QString & str) const
{
  return QRegExp("\\s*").exactMatch(str);
}
/*******************************************************************************/


