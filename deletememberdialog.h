#ifndef DELETEMEMBERDIALOG_H
#define DELETEMEMBERDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "database_manager.h"

namespace Ui {
class DeleteMemberDialog;
}

class DeleteMemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteMemberDialog(QWidget *parent = nullptr);
    ~DeleteMemberDialog();

private slots:
    void on_btn_cancel_clicked();

    void on_btn_OK_clicked();

private:
    Ui::DeleteMemberDialog *ui;
};

#endif // DELETEMEMBERDIALOG_H
