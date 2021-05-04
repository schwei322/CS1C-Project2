#include "additemdialog.h"
#include "ui_additemdialog.h"
#include <QMessageBox>


/****************************************************************************//**
 *      Contructor
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

AddItemDialog::AddItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
}
/*******************************************************************************/



/****************************************************************************//**
 *      Deconstructor
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

AddItemDialog::~AddItemDialog()
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

// When ok is selected, check if inputs are valid.
void AddItemDialog::on_btn_OK_clicked()
{
    Database_manager bulk_club_database;
    QMessageBox errorMessageBox;
    QString item_name = ui->lineEdit_itemName->text();
    QString item_price = ui->lineEdit_teamName_3->text();

    if (isInputValid(item_name, item_price))
    {
        qDebug() << "Inputs were valid.";
        bulk_club_database.add_item(item_name, item_price);
        QDialog::close();
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

void AddItemDialog::on_btn_cancel_clicked()
{
    QWidget::close();
}
/*******************************************************************************/



/****************************************************************************//**
 *      isInputValid
 * ____________________________________________________________________________
 *
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return N/A
*******************************************************************************/

bool AddItemDialog::isInputValid(QString &item_name, QString &item_price)
{
    bool inputValid = true;
    int countDecimal = 0;
    QMessageBox errorMessageBox;

    // No field can be left empty
    if (item_name.isEmpty() || item_price.isEmpty())
    {
        errorMessageBox.setText("INVALID INPUT:\nALL fields must be entered.");
        errorMessageBox.exec();
        inputValid = false;
    }

    // item_price can only contain digits, commas, and one period as decimal.
    for (int i = 0; i < item_price.size(); i++)
    {
        // Check if only digits, commas, and periods present
        if ( !(item_price[i].isDigit() || item_price[i] == "," || item_price[i] == ".") )
        {
            errorMessageBox.setText("INVALID INPUT:\nPrice for item can only contain numbers, commas (optional), and one decimal");
            inputValid = false;
            errorMessageBox.exec();
            break;
        }
        if (item_price[i] == ".")
        {
            countDecimal++;
        }
        if (countDecimal > 1)
        {
            errorMessageBox.setText("INVALID INPUT:\nPrice can only contain one decimal.");
            inputValid = false;
            errorMessageBox.exec();
            break;
        }
    }

    return inputValid;
}
/*******************************************************************************/



/****************************************************************************//**
 *      _______
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


















