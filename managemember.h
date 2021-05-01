#ifndef MANAGEMEMBER_H
#define MANAGEMEMBER_H

#include <QWidget>

namespace Ui {
class ManageMember;
}

class ManageMember : public QWidget
{
    Q_OBJECT

public:
    explicit ManageMember(QWidget *parent = nullptr);
    ~ManageMember();

private:
    Ui::ManageMember *ui;
};

#endif // MANAGEMEMBER_H
