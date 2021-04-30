#include "mainwindow.h"
#include <QApplication>
#include "database_manager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    /**********************************************/
    // Querying database using database_manager class.

    // Database_manager db;

    // qDebug() << db.get_memberInfo("88888") << "\n";
    //qDebug() <<db.get_memberPurchases("88888") << "\n";
    //qDebug() <<db.get_itemInfo("Coke");

    //db.update_totalAmountSpent("88888", "123");
    //db.insert_row_in_inventory("a_name", "a_sellQuantity", "a_totalRevenue");
    //db.delete_row_in_inventory("a_name");

    /**********************************************/

    // exit(0); // Prevents window from opening

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
