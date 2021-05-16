#ifndef MEMBER_H
#define MEMBER_H

#include <QtCore>
typedef int Date; // ***Remove after you impliment Date class.***

/// Member class also
///
/// Detailed Description
class Member
{
private:
    QString name;
    int membership_number;
    QString membership_type;
    QString membership_expiration_date;
    double total_amount_spent;
    double rebate_amount;

public:
    Member();
    Member(QString name, int membership_number, QString membership_type, QString membership_expiration_date, double total_amount_spent, double rebate_amount);
    ~Member();

    // Accessor Methods
    QString get_name() const;
    int get_membership_number() const;
    QString get_membership_type() const;
    QString get_membership_expiration_date() const;
    double get_total_amount_spent() const;
    double get_rebate_amount() const;

    // Mutator Methods
    void set_name(QString name);
    void set_membership_number(int membership_number);
    void set_membership_type(QString membership_type);
    void set_membership_expiration_date(QString membership_expiration_date);
    void set_total_amount_spent(double total_amount_spent);
    void set_rebate_amount(double rebate_amount);

};

#endif // MEMBER_H
