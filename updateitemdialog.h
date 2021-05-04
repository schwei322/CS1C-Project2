#ifndef UPDATEITEMDIALOG_H
#define UPDATEITEMDIALOG_H

#include <QDialog>
#include <QDebug>
#include "database_manager.h"
#include <QMessageBox>

namespace Ui {
class UpdateItemDialog;
}

class UpdateItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateItemDialog(QWidget *parent = nullptr);
    ~UpdateItemDialog();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_OK_clicked();

private:
    Ui::UpdateItemDialog *ui;
};

#endif // UPDATEITEMDIALOG_H
