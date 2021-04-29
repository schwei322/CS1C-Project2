#include "purchasedata.h"

PurchaseData::PurchaseData()
{

}

void PurchaseData::setDate(QString date)
{
    this->date = date;
}
void PurchaseData::setMembershipNumber(QVariant memberShipNumber)
{
    this->memberShipNumber = memberShipNumber;
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
