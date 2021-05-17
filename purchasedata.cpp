#include "purchasedata.h"

/**
 * @brief constructor
 * @param date, name, membershipNumber,product, price, quantity
 */
PurchaseData::PurchaseData()
{
    this->date = "";
    this->name = "";
    this->membershipNumber = 0;
    this->product = "";
    this->price = 0.0;
    this->quantity = 0;
}
/**
 * @brief Accessor to get the date
 * @return date
 */
QString PurchaseData::getDate() const
{
    return this->date;
}
/**
 * @brief Accesor to get the name
 * @return name
 */
QString PurchaseData::getName() const
{
    return this->name;
}
/**
 * @brief Accesor to get MembershipNumber
 * @return membershipNumber
 */
int PurchaseData::getMembershipNumber() const
{
    return this->membershipNumber;
}
/**
 * @brief accesor to get Product
 * @return product
 */
QString PurchaseData::getProduct() const
{
    return this->product;
}
/**
 * @brieaccessor to get Price
 * @return price
 */
float PurchaseData::getPrice() const
{
    return this->price;
}
/**
 * @brief Accessor to get Quantity
 * @return quantity
 */
int PurchaseData::getQuantity() const
{
    return this->quantity;
}
/**
 * @brief mutator to set Date
 * @param date
 */
void PurchaseData::setDate(QString date)
{
    this->date = date;
}
/**
 * @brief mutator to set Name
 * @param name
 */
void PurchaseData::setName(QString name)
{
    this->name = name;
}
/**
 * @brief  mutator to set MembershipNumber
 * @param membershipNumber
 */
void PurchaseData::setMembershipNumber(int membershipNumber)
{
    this->membershipNumber = membershipNumber;
}
/**
 * @brief mutator to set Product
 * @param product
 */
void PurchaseData::setProduct(QString product)
{
    this->product = product;
}
/**
 * @brief  mutator to set Price
 * @param price
 */
void PurchaseData::setPrice(float price)
{
    this->price = price;
}
/**
 * @brief mutator to set Quantity
 * @param quantity
 */
void PurchaseData::setQuantity(int quantity)
{
    this->quantity = quantity;
}
/**
 * @brief PurchaseData::operator ==
 * @param otherPurchaseData
 * @return
 */
bool PurchaseData::operator==(const PurchaseData& otherPurchaseData)
{
    return this->product == otherPurchaseData.product;
}
/**
 * @brief MemberPurchaseData::MemberPurchaseData
 */
MemberPurchaseData::MemberPurchaseData()
{
    this->membershipType = "";
    this->expirationDate = "";
    this->totalSpent = 0.0;
}
/**
 * @brief get MembershipType
 * @return membership type
 */
QString MemberPurchaseData::getMembershipType() const
{
    return this->membershipType;
}
/**
 * @brief get the Expiration Date
 * @return expiration date
 */
QString MemberPurchaseData::getExpirationDate() const
{
    return this->expirationDate;
}
/**
 * @brief get Total Spent
 * @return total spent
 */
double MemberPurchaseData::getTotalSpent() const
{
    return this->totalSpent;
}
/**
 * @brief get Rebate Amount
 * @return rebate amount
 */
double MemberPurchaseData::getRebateAmount() const
{
    return this->rebateAmount;
}
/**
 * @brief set Membership Type
 * @param membershipType
 */
void MemberPurchaseData::setMembershipType(QString membershipType)
{
    this->membershipType = membershipType;
}
/**
 * @brief set Expiration Date
 * @param expiration Date
 * @return expiration Date
 */
void MemberPurchaseData::setExpirationDate(QString expirationDate)
{
    this->expirationDate = expirationDate;
}
/**
 * @brief set Total Spent
 * @param totalSpent
 */
void MemberPurchaseData::setTotalSpent(double totalSpent)
{
    this->totalSpent = totalSpent;
}
/**
 * @brief set Rebate Amount
 * @param rebateAmount
 */
void MemberPurchaseData::setRebateAmount(double rebateAmount)
{
    this->rebateAmount = rebateAmount;
}

