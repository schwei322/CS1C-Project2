#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtGui>
#include <QSqlQueryModel>

namespace Ui {
class AddItem;
}

class AddItem : public QDialog
{
    Q_OBJECT

public:
    explicit AddItem(QWidget *parent = nullptr);
    ~AddItem();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddItem *ui;
};

#endif // ADDITEM_H
