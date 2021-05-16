#include "member.h"

/****************************************************************************//**
 *      Default Constructor
 *____________________________________________________________________________
 *
 *******************************************************************************/

Member::Member()
{
    this->name = "";
    this->membership_number = 0;
    this->membership_type = "Regular";
    this->membership_expiration_date = "";
    this->total_amount_spent = 0.0;
    this->rebate_amount = 0.0;
}
/********************************************************************************/



/****************************************************************************//**
 *      Overloaded Constructor
 *____________________________________________________________________________
 *
 *******************************************************************************/

Member::Member(QString name, int membership_number, QString membership_type,
               QString membership_expiration_date, double total_amount_spent, double rebate_amount)
{
    this->name = name;
    this->membership_number = membership_number;
    this->membership_type = membership_type;
    this->membership_expiration_date = membership_expiration_date;
    this->total_amount_spent = total_amount_spent;
    this->rebate_amount = rebate_amount;
}
/********************************************************************************/



/****************************************************************************//**
 *      Deconstructor
 *____________________________________________________________________________
 *
 *******************************************************************************/
Member::~Member(){}
/*******************************************************************************/



/****************************************************************************//**
 *      get_name
 * ____________________________________________________________________________
 * Method gets name for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return name : QString representing name of a member.
********************************************************************************/

QString Member::get_name() const
{
    qDebug() << name << "GET NAM EGET NAME\n";
    return name;
}
/*******************************************************************************/



/****************************************************************************//**
 *      get_membership_number
 * ____________________________________________________________________________
 * Method gets membership number for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return membership_number : int representing membership_number.
********************************************************************************/

int Member::get_membership_number() const
{
    return membership_number;
}
/*******************************************************************************/



/****************************************************************************//**
 *      get_membership_type
 * ____________________________________________________________________________
 * Method gets membership type for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return membership_type : QString representing membership type.
********************************************************************************/

QString Member::get_membership_type() const
{
    return membership_type;
}
/*******************************************************************************/



/****************************************************************************//**
 *      get_membership_expiration_date
 * ____________________________________________________________________________
 * Method gets membership expiration date for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return membership_expiration_date : QString representing expiration date.
********************************************************************************/

QString Member::get_membership_expiration_date() const
{
    return membership_expiration_date;
}
/*******************************************************************************/



/****************************************************************************//**
 *      get_total_amount_spent
 * ____________________________________________________________________________
 * Method gets total amount spent of a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return total_amount_spent : total amount spent by the instance.
********************************************************************************/

double Member::get_total_amount_spent() const
{
    return total_amount_spent;
}
/*******************************************************************************/



/****************************************************************************//**
 *      get_rebate_amount
 * ____________________________________________________________________________
 * Method gets rebate amount for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param N/A
 *
 * \b OUTPUT:
 *      @return rebate_amount : rebate amount attribute of instance.
********************************************************************************/

double Member::get_rebate_amount() const
{
    return rebate_amount;
}
/*******************************************************************************/



/****************************************************************************//**
 *      set_name
 * ____________________________________________________________________________
 * Method changes the name of a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param name : QString representing name of a member.
 *
 * \b OUTPUT:
 *      @return N/A
********************************************************************************/

void Member::set_name(QString name)
{
    this->name = name;
}
/*******************************************************************************/



/****************************************************************************//**
 *      set_membership_number
 * ____________________________________________________________________________
 * Method changes membership number for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param membership_number : int representing membership_number.
 *
 * \b OUTPUT:
 *      @return N/A
********************************************************************************/

void Member::set_membership_number(int membership_number)
{
    this->membership_number = membership_number;
}
/*******************************************************************************/




/****************************************************************************//**
 *      set_membership_type
 * ____________________________________________________________________________
 * Method changes membership type for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param membership_type : QString representing membership type.
 *
 * \b OUTPUT:
 *      @return N/A
********************************************************************************/

void Member::set_membership_type(QString membership_type)
{
    this->membership_type = membership_type;
}
/*******************************************************************************/


/****************************************************************************//**
 *      set_membership_expiration_date
 * ____________________________________________________________________________
 * Method changes membership expiration data for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param membership_expiration_date : QString representing expiration date.
 *
 * \b OUTPUT:
 *      @return N/A
********************************************************************************/

void Member::set_membership_expiration_date(QString membership_expiration_date)
{
    this->membership_expiration_date = membership_expiration_date;
}
/*******************************************************************************/



/****************************************************************************//**
 *      set_total_amount_spent
 * ____________________________________________________________________________
 * Method sets total amount spent attribute for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param total_amount_spent : total amount spent by the instance.
 *
 * \b OUTPUT:
 *      @return N/A
********************************************************************************/

void Member::set_total_amount_spent(double total_amount_spent)
{
    this->total_amount_spent = total_amount_spent;
}
/*******************************************************************************/

/****************************************************************************//**
 *      set_rebate_amount
 * ____________________________________________________________________________
 * Method sets rebate amount for a Member instance.
 * ____________________________________________________________________________
 * \b INPUT:
 *      @param  rebate_amount : rebate amount attribute of instance.
 *
 * \b OUTPUT:
 *      @return N/A
********************************************************************************/

void Member::set_rebate_amount(double rebate_amount)
{
    this->rebate_amount = rebate_amount;
}
/*******************************************************************************/


