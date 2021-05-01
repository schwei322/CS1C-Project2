#ifndef DELETEITEM_H
#define DELETEITEM_H

#include <QDialog>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QSqlQueryModel>

namespace Ui {
class DeleteItem;
}

class DeleteItem : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteItem(QWidget *parent = nullptr);
    ~DeleteItem();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeleteItem *ui;
};

#endif // DELETEITEM_H
