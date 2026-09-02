#include "header.h"

int date_validate(struct date dt)
{
    if (dt.day > 31 || dt.day < 1 || dt.month < 1 || dt.month > 12 || dt.year < 1000 || dt.year > 9999)
        return 0;
    if (dt.month > 12)
        return 0;
    if (dt.month == 1 && dt.day > 31)
        return 0;
    if(dt.month == 2 && (dt.year % 400 == 0 || (dt.year % 100 != 0 && dt.year % 4 == 0)) && dt.day > 29)
        return 0;
    if(dt.month == 2 && !(dt.year % 400 == 0 || (dt.year % 100 != 0 && dt.year % 4 == 0)) && dt.day > 28)
        return 0;
    if (dt.month == 3 && dt.day > 31)
        return 0;
    if (dt.month == 4 && dt.day > 30)
        return 0;
    if (dt.month == 5 && dt.day > 31)
        return 0;
    if (dt.month == 6 && dt.day > 30)
        return 0;
    if (dt.month == 7 && dt.day > 31)
        return 0;
    if (dt.month == 8 && dt.day > 31)
        return 0;
    if (dt.month == 9 && dt.day > 30)
        return 0;
    if (dt.month == 10 && dt.day > 31)
        return 0;
    if (dt.month == 11 && dt.day > 30)
        return 0;
    if (dt.month == 12 && dt.day > 31)
        return 0;
    return 1;
}