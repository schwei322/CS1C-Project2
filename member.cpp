#include "member.h"
#include <iostream>
using namespace std;

Member::Member()
{

}

QString Member::getName()
{
    return this->name;
}
int Member::getMembershipNumber()
{
    return this->membershipNumber;
}
QString Member::getMemberType()
{
    return this->memberType;
}
QString Member::getExpirationDate()
{
    return this->expirationDate;
}
float Member::getTotalAmountSpent()
{
    return this->totalAmountSpent;
}
float Member::getRebateAmount()
{
    return this->rebateAmount;
}
void Member::setName(QString name)
{
    this->name = name;
}
void Member::setMembershipNumber(int membershipNumber)
{
    this->membershipNumber = membershipNumber;
}
void Member::setMemberType(QString memberType)
{
    this->memberType = memberType;
}
void Member::setExpirationDate(QString expirationDate)
{
    this->expirationDate = expirationDate;
}
void Member::setTotalAmountSpent(float totalAmountSpent)
{
    this->totalAmountSpent = totalAmountSpent;
}
void Member::setRebateAmount(float rebateAmount)
{
    this->rebateAmount = rebateAmount;
}

bool Member::operator==(const Member& otherMember)
{
    return this->membershipNumber == otherMember.membershipNumber;
}

void Member::print() const
{
    cout << membershipNumber << endl;
}



float memberPurchase::getPrice()
{
    return this->price;
}

int memberPurchase::getQuantity()
{
    return this->quantity;
}

void memberPurchase::setPrice(float price)
{
    this->price = price;
}

void memberPurchase::setQuantity(int quantity)
{
    this->quantity = quantity;
}
void memberPurchase::print() const
{
   Member::print();
}
