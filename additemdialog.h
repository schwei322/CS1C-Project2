#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QDebug>
#include "database_manager.h"

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemDialog(QWidget *parent = nullptr);
    ~AddItemDialog();

    bool isInputValid(QString &item_name, QString &item_price);


private slots:
    void on_buttonBox_accepted();

    void on_btn_OK_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::AddItemDialog *ui;
};

#endif // ADDITEMDIALOG_H
