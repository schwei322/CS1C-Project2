#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include "managemem.h"
#include "manageitem.h"
namespace Ui {
class Admin;
}

class Admin : public QWidget
{
    Q_OBJECT
    ManageMem * memberMangeWindow;
    ManageItem * manageItemWindow;

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
