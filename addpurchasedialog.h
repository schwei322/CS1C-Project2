#ifndef ADDPURCHASEDIALOG_H
#define ADDPURCHASEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "database_manager.h"
#include <QString>
#include "miscellaneous_functions.h"

namespace Ui {
class AddPurchaseDialog;
}

class AddPurchaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPurchaseDialog(QWidget *parent = nullptr);
    ~AddPurchaseDialog();
    bool check_lineEdits(QString& memberID, QString& product_name, QString& product_price, QString& quantity,  QString& date) const;
    bool isWhiteSpace(const QString & str) const;

private slots:
    void on_btn_OK_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::AddPurchaseDialog *ui;
};


#endif // ADDPURCHASEDIALOG_H
