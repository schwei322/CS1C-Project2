#ifndef MEMBERSHIPMANAGEMENT_H
#define MEMBERSHIPMANAGEMENT_H

#include <QWidget>

namespace Ui {
class membershipManagement;
}

class membershipManagement : public QWidget
{
    Q_OBJECT

public:
    explicit membershipManagement(QWidget *parent = nullptr);
    ~membershipManagement();

private:
    Ui::membershipManagement *ui;
};

#endif // MEMBERSHIPMANAGEMENT_H
