#ifndef CHECKRABATES_H
#define CHECKRABATES_H

#include <QWidget>
#include <QtDebug>
#include <QTableWidgetItem>

#include "database_manager.h"
#include "purchasedata.h"
#include "member.h"

namespace Ui {
class checkRabates;
}

class checkRabates : public QWidget
{
    Q_OBJECT

public:
    explicit checkRabates(QWidget *parent = nullptr);
    ~checkRabates();

    void calTotalSpent();
    void displayRebates();
private slots:
    void on_pushButton_clicked();

private:
    Ui::checkRabates *ui;
    DatabaseManager database_manager;
};

#endif // CHECKRABATES_H
