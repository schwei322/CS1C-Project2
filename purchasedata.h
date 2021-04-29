#ifndef PURCHASEDATA_H
#define PURCHASEDATA_H

#include <QString>
#include <QVariant>



class PurchaseData
{
public:
    PurchaseData();
    void setDate(QString date);
    void setMembershipNumber(QVariant memberShipNumber);
    void setProduct(QString product);
    void setPrice(float price);
    void setQuantity(QVariant quantity);
private:
    QString date;
    QVariant memberShipNumber;
    QString product;
    float price;
    QVariant quantity;
};

#endif // PURCHASEDATA_H
