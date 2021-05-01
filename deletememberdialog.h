#ifndef DELETEMEMBERDIALOG_H
#define DELETEMEMBERDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteMemberDialog;
}

class DeleteMemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteMemberDialog(QWidget *parent = nullptr);
    ~DeleteMemberDialog();

private:
    Ui::DeleteMemberDialog *ui;
};

#endif // DELETEMEMBERDIALOG_H
