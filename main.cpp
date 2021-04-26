#include "mainwindow.h"

#include <QApplication>
#include "database_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    /**********************************************/
    // Querying database using database_manager class.

    Database_manager db;

    //qDebug() << db.get_memberInfo("88888");
    //qDebug() <<db.get_memberPurchases("88888") << "\n\n";
    qDebug() <<db.get_itemInfo("Coke");




    /**********************************************/



    exit(0); // Prevents window from opening
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
