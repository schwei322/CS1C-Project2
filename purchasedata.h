#ifndef PURCHASEDATA_H
#define PURCHASEDATA_H

#include <QString>
#include <QVariant>

class PurchaseData
{
public:
    PurchaseData();

    QString getDate() const;
    QString getName() const;
    int getMembershipNumber() const;
    QString getProduct() const;
    float getPrice() const;
    int getQuantity() const;

    void setDate(QString date);
    void setName(QString name);
    void setMembershipNumber(int membershipNumber);
    void setProduct(QString product);
    void setPrice(float price);
    void setQuantity(int quantity);

    bool operator==(const PurchaseData& otherPurchaseData);

private:
    QString date;
    QString name;
    int membershipNumber;
    QString product;
    float price;
    int quantity;

};

class MemberPurchaseData : public PurchaseData
{
public:
    MemberPurchaseData();

    double getTotalSpent() const;

    void setTotalSpent(double totalSpent);

private:
    double totalSpent;

};

#endif // PURCHASEDATA_H
