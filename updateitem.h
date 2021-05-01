#ifndef UPDATEITEM_H
#define UPDATEITEM_H

#include <QDialog>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QSqlQueryModel>

namespace Ui {
class UpdateItem;
}

class UpdateItem : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateItem(QWidget *parent = nullptr);
    ~UpdateItem();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::UpdateItem *ui;
};

#endif // UPDATEITEM_H
