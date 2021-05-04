#ifndef ADDMEMBERDIALOG_H
#define ADDMEMBERDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QButtonGroup>
#include "database_manager.h"

namespace Ui {
class AddMemberDialog;
}

class AddMemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMemberDialog(QWidget *parent = nullptr);
    ~AddMemberDialog();

private slots:
    void on_btn_OK_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::AddMemberDialog *ui;
};

#endif // ADDMEMBERDIALOG_H
