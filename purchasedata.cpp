#include "purchasedata.h"

PurchaseData::PurchaseData()
{

}

void PurchaseData::setDate(QString date)
{
    this->date = date;
}
void PurchaseData::setMembershipNumber(QVariant membershipNumber)
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

void PurchaseData::setQuantity(QVariant quantity)
{
    this->quantity = quantity;
}

QString PurchaseData::getDate()
{
    return this->date;
}
QVariant PurchaseData::getMembershipNumber()
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
QVariant PurchaseData::getQuantity()
{
    return this->quantity;
}
