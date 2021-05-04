#ifndef DELETEITEMDIALOG_H
#define DELETEITEMDIALOG_H

#include <QDialog>
#include "database_manager.h"
#include <QMessageBox>

namespace Ui {
class DeleteItemDialog;
}

class DeleteItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteItemDialog(QWidget *parent = nullptr);
    ~DeleteItemDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::DeleteItemDialog *ui;
};

#endif // DELETEITEMDIALOG_H
