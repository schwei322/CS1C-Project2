#ifndef MANAGEMEM_H
#define MANAGEMEM_H

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
#include "adddialog.h"
#include "deletedialog.h"

namespace Ui {
class ManageMem;
}

class ManageMem : public QWidget
{
    Q_OBJECT
    AddDialog * addDialogWindow;
    DeleteDialog * deleteDialogWindow;

public:
    explicit ManageMem(QWidget *parent = nullptr);
    ~ManageMem();

private slots:
    void on_pushButton_load_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::ManageMem *ui;
};

#endif // MANAGEMEM_H
