#ifndef PURCHASEDATA_H
#define PURCHASEDATA_H

#include <QString>
#include <QVariant>



class PurchaseData
{
public:
    PurchaseData();

    QString getDate();
    int getMembershipNumber();
    QString getProduct();
    float getPrice();
    int getQuantity();

    void setDate(QString date);
    void setMembershipNumber(int membershipNumber);
    void setProduct(QString product);
    void setPrice(float price);
    void setQuantity(int quantity);

    bool operator==(const PurchaseData& otherPurchaseData);

private:
    QString date;
    int membershipNumber;
    QString product;
    float price;
    int quantity;

};

#endif // PURCHASEDATA_H
