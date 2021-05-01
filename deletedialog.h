#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QSqlQueryModel>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeleteDialog *ui;
};

#endif // DELETEDIALOG_H
