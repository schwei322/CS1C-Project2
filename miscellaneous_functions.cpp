#include "miscellaneous_functions.h"

// NOTE: Function does NOT work!
double string_to_double(QString str)
{
    double double_value;
    QString digits;
    QString dec_digits;

    // Stores number left of decimal place.
    digits = str.split(".")[0];

    // Stores number right of decimal place
    dec_digits = str.split(".")[1];

    // Remove comma from digits
    digits = (digits.split(",")[0]) + (digits.split(",")[1]);

    // Prepend decimal to front of decimal_digits
    dec_digits.prepend(".");

    // Append decimal to digits
    digits.append(".000");

    double_value = ( digits.toDouble() + dec_digits.toDouble() );


    qDebug() << digits.toDouble();
    qDebug() << dec_digits.toDouble();
    qDebug() << double_value;

    return double_value;
}


bool checkIfEmpty(const QString contents)
{
     if(contents.trimmed()=="") return true;
     else return false;
}
