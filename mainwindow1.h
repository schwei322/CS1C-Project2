#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include <QtDebug>

#include "database_manager.h"
#include "purchasedata.h"
#include "checkrabates.h"
namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();

private:
    Ui::MainWindow1 *ui;
};

#endif // MAINWINDOW1_H
