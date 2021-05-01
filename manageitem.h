#ifndef MANAGEITEM_H
#define MANAGEITEM_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QDebug>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>
#include "additem.h"
#include "deleteitem.h"
#include "updateitem.h"

namespace Ui {
class ManageItem;
}

class ManageItem : public QWidget
{
    Q_OBJECT
    AddItem * addItemWindow;
    DeleteItem * deleteItemWindow;
    UpdateItem * updateItemWindow;

public:
    explicit ManageItem(QWidget *parent = nullptr);
    ~ManageItem();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ManageItem *ui;
};

#endif // MANAGEITEM_H
