#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    /**********************************************/
    // Querying database using database_manager class.

    Database_manager db;

    //qDebug() << db.get_memberInfo("77777") << "\n";
    //qDebug() << db.get_memberPurchases("77777") << "\n";
    //qDebug() <<db.get_itemInfo("Rack of Lamb");

    //db.update_totalAmountSpent("88888", "541351");
    //db.update_totalAmountSpent("77777", "45456456456456546");

    //db.insert_row_in_inventory("someItem", "5", "123", "1000");
    //db.insert_row_in_inventory("bbb", "bbb", "bbb", "bbb");
    //db.insert_row_in_inventory("ccc", "ccc", "ccc", "ccc");
    //db.insert_row_in_inventory("ddd", "ddd", "dddd", "dddd");

    db.delete_row_in_inventory("someItem");
    db.delete_row_in_inventory("bbb");
    db.delete_row_in_inventory("ccc");
    db.delete_row_in_inventory("ddd");

    //db.delete_row_in_inventory("a_name");

    /**********************************************/

    exit(0); // Prevents window from opening
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
