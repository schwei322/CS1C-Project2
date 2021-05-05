#include "purchasedata.h"

PurchaseData::PurchaseData()
{

}

QString PurchaseData::getDate()
{
    return this->date;
}

int PurchaseData::getMembershipNumber()
{
    return this->membershipNumber;
}

QString PurchaseData::getProduct()
{
    return this->product;
}

float PurchaseData::getPrice()
{
    return this->price;
}

int PurchaseData::getQuantity()
{
    return this->quantity;
}

void PurchaseData::setDate(QString date)
{
    this->date = date;
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
