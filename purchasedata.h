/**
 *  @file purchasedata.h
 *  @brief handles member, sort by expiration month, gets total rebate and total spent
*/
#ifndef PURCHASEDATA_H
#define PURCHASEDATA_H

#include <QString>
#include <QVariant>

/// Brief description
///
/// Detailed Description
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
    /**
     * @brief obtains Product
     */
    QString getProduct() const;
    /**
     * @brief  obtains Price
     */
    float getPrice() const;
    /**
     * @brief  obtains Quantity
     */
    int getQuantity() const;
    /**
     * @brief Sort data by date
     * @param date
     */
    void setDate(QString date);
    /**
     * @brief set Name
     * @param name
     */
    void setName(QString name);
    /**
     * @brief set Membership Number
     * @param membershipNumber
     */
    void setMembershipNumber(int membershipNumber);
    /**
     * @brief set Product
     * @param product
     */
    void setProduct(QString product);
    /**
     * @brief set Price
     * @param price
     */
    void setPrice(float price);
    /**
     * @brief set Quantity
     * @param quantity
     */
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
