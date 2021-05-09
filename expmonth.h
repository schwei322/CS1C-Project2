#ifndef EXPMONTH_H
#define EXPMONTH_H

#include <QDialog>
#include "database_manager.h"

namespace Ui {
class expMonth;
}

class expMonth : public QDialog
{
    Q_OBJECT

public:
    explicit expMonth(QWidget *parent = nullptr, DatabaseManager *dbm = nullptr);
    ~expMonth();

private slots:
    //void on_lineEdit_editingFinished();

    void on_comboBox_currentIndexChanged();

private:
    DatabaseManager *dbm;
    Ui::expMonth *ui;
};

#endif // EXPMONTH_H
