#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QVariant>


class Member
{
public:
    Member();

    QString getName();
    int getMembershipNumber();
    QString getMemberType();
    QString getExpirationDate();
    float getTotalAmountSpent();
    float getRebateAmount();


    void setName(QString name);
    void setMembershipNumber(int membershipNumber);
    void setMemberType(QString memberType);
    void setExpirationDate(QString expirationDate);
    void setTotalAmountSpent(float totalAmountSpent);
    void setRebateAmount(float rebateAmount);

    bool operator==(const Member& otherMember);

    void print() const;

private:
    QString name;
    int membershipNumber;
    QString memberType;
    QString expirationDate;
    float totalAmountSpent;
    float rebateAmount;
};

class memberPurchase: public Member
{
private:
    float price;
    int quantity;
public:
    float getPrice();
    int getQuantity();

    void setPrice(float price);
    void setQuantity(int quantity);

    void print() const;
};

#endif // MEMBER_H
