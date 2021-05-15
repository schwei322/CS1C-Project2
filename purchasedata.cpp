#include "purchasedata.h"

PurchaseData::PurchaseData()
{
    this->date = "";
    this->name = "";
    this->membershipNumber = 0;
    this->product = "";
    this->price = 0.0;
    this->quantity = 0;
}

QString PurchaseData::getDate() const
{
    return this->date;
}

QString PurchaseData::getName() const
{
    return this->name;
}

int PurchaseData::getMembershipNumber() const
{
    return this->membershipNumber;
}

QString PurchaseData::getProduct() const
{
    return this->product;
}

float PurchaseData::getPrice() const
{
    return this->price;
}

int PurchaseData::getQuantity() const
{
    return this->quantity;
}

void PurchaseData::setDate(QString date)
{
    this->date = date;
}

void PurchaseData::setName(QString name)
{
    this->name = name;
}

void PurchaseData::setMembershipNumber(int membershipNumber)
{
    this->membershipNumber = membershipNumber;
}

void PurchaseData::setProduct(QString product)
{
    this->product = product;
}

void PurchaseData::setPrice(float price)
{
    this->price = price;
}

void PurchaseData::setQuantity(int quantity)
{
    this->quantity = quantity;
}

bool PurchaseData::operator==(const PurchaseData& otherPurchaseData)
{
    return this->product == otherPurchaseData.product;
}

MemberPurchaseData::MemberPurchaseData()
{
    this->membershipType = "";
    this->expirationDate = "";
    this->totalSpent = 0.0;
}

QString MemberPurchaseData::getMembershipType() const
{
    return this->membershipType;
}

QString MemberPurchaseData::getExpirationDate() const
{
    return this->expirationDate;
}

double MemberPurchaseData::getTotalSpent() const
{
    return this->totalSpent;
}

double MemberPurchaseData::getRebateAmount() const
{
    return this->rebateAmount;
}

void MemberPurchaseData::setMembershipType(QString membershipType)
{
    this->membershipType = membershipType;
}

void MemberPurchaseData::setExpirationDate(QString expirationDate)
{
    this->expirationDate = expirationDate;
}

void MemberPurchaseData::setTotalSpent(double totalSpent)
{
    this->totalSpent = totalSpent;
}

void MemberPurchaseData::setRebateAmount(double rebateAmount)
{
    this->rebateAmount = rebateAmount;
}

