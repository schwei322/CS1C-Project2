#ifndef PURCHASEDATA_H
#define PURCHASEDATA_H

#include <QString>
#include <QVariant>



class PurchaseData
{
public:
    PurchaseData();
    void setDate(QString date);
    void setMembershipNumber(QVariant membershipNumber);
    void setProduct(QString product);
    void setPrice(float price);
    void setQuantity(QVariant quantity);

    QString getDate();
    QVariant getMembershipNumber();
    QString getProduct();
    float getPrice();
    QVariant getQuantity();
private:
    QString date;
    QVariant membershipNumber;
    QString product;
    float price;
    QVariant quantity;
};

#endif // PURCHASEDATA_H
