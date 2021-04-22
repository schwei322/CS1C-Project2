#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Item
{
private:
    QString itemName;
    double itemPrice;
    double salesQual;
public:
    Item();
    Item(QString itemName,  double itemPrice, double salesQual);
    double calc_totalRevenue(double itemPrice, double salesQual);
};



#endif // ITEM_H
