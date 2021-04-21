#ifndef MEMBER_H
#define MEMBER_H

#include <QtCore>

/// Brief Description
///
/// Detailed Description
class Member
{
private:
    QString name;
    int* membership_number;
    QString membership_type;
    Date membership_expiration_date;
    double total_amount_spent;
    double rebate_amount;

public:
    Member();
    Member(QString name, int* membership_number, QString membership_type, Date membership_expirationDate, double total_amountSpend, double rebateAmount);
    ~Member();

    // Computational Methods
    double calc_rebate() const;
    double calc_annual_dues() const;

    // Accessor Methods
    QString get_name();
    int* get_membership_number();
    QString get_membership_type();
    Date get_membership_expiration_date();
    double get_total_amount_spent();
    double get_rebate_amount();

    // Mutator Methods
    void set_name() const;
    void set_membership_number() const;
    void set_membership_type() const;
    void set_membership_expiration_date() const;
    void set_total_amount_spent() const;
    void set_rebate_amount() const;
};

#endif // MEMBER_H
