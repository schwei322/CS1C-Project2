#ifndef MEMBER_H
#define MEMBER_H

#include <QtCore>
typedef int Date; // ***Remove after you impliment Date class.***

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
    Member(QString name, int* membership_number, QString membership_type, Date membership_expiration_date, double total_amount_spent, double rebate_amount);
    Member(Member& mem);
    ~Member();

    // Computational Methods
    double calc_rebate() const;
    double calc_annual_dues() const;

    // Accessor Methods
    QString get_name() const;
    int* get_membership_number() const;
    QString get_membership_type() const;
    Date get_membership_expiration_date() const;
    double get_total_amount_spent() const;
    double get_rebate_amount() const;

    // Mutator Methods
    void set_name(QString name);
    void set_membership_number(int* membership_number);
    void set_membership_type(QString membership_type);
    void set_membership_expiration_date(Date membership_expiration_date);
    void set_total_amount_spent(double total_amount_spent);
    void set_rebate_amount(double rebate_amount);
};

#endif // MEMBER_H