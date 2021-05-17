#ifndef PURCHASEDATA_H
#define PURCHASEDATA_H

#include <QString>
#include <QVariant>

class PurchaseData
{
public:
    /**
     * @brief holds information about Data Purchased
     */
    PurchaseData();
    /**
     * @brief obtains Date
     */
    QString getDate() const;
    /**
     * @brief  obtains Name
     */
    QString getName() const;
    /**
     * @brief  obtains Membership Number
     */
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

    QString getMembershipType() const;
    QString getExpirationDate() const;
    double getTotalSpent() const;
    double getRebateAmount() const;

    void setMembershipType(QString membershipType);
    void setExpirationDate(QString expirationDate);
    void setTotalSpent(double totalSpent);
    void setRebateAmount(double rebateAmount);

private:
    QString membershipType;
    QString expirationDate;
    double totalSpent;
    double rebateAmount;

};

#endif // PURCHASEDATA_H
