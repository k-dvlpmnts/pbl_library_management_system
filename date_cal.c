#include "header.h"

void date_cal(struct date i, struct date *d)
{
    do{
        if (i.month > 12)
        {
            i.month -= 12;
            i.year++;
        }
        i.day += 30;
        if(i.month == 1)
            if (i.day > 31)
            {
                i.day -= 31;
                i.month++;
            }
        if(i.month == 2 && (i.year % 400 == 0 || (i.year % 100 != 0 && i.year % 4 == 0)))
            if (i.day > 29)
            {
                i.day -= 29;
                i.month++;
            }
        if(i.month == 2 && !(i.year % 400 == 0 || (i.year % 100 != 0 && i.year % 4 == 0)))
            if (i.day > 28)
            {
                i.day -= 28;
                i.month++;
            }
        if(i.month == 3)
            if (i.day > 31)
            {
                i.day -= 31;
                i.month++;
            }
        if(i.month == 4)
            if (i.day > 30)
            {
                i.day -= 30;
                i.month++;
            }
        if(i.month == 5)
            if (i.day > 31)
            {
                i.day -= 31;
                i.month++;
            }
        if(i.month == 6)
            if (i.day > 30)
            {
                i.day -= 30;
                i.month++;
            }
        if(i.month == 7)
            if (i.day > 31)
            {
                i.day -= 31;
                i. month++;
            }
        if(i.month == 8)
            if (i.day > 31)
            {
                i.day -= 31;
                i.month++;
            }
        if(i.month == 9)
            if (i.day > 30)
            {
                i.day -= 30;
                i.month++;
            }
        if(i.month == 10)
            if (i.day > 31)
            {
                i.day -= 31;
                i.month++;
            }
        if(i.month == 11)
            if (i.day > 30)
            {
                i.day -= 30;
                i.month++;
            }
        if(i.month == 12)
            if (i.day > 31)
            {
                i.day -= 31;
                i.month++;
            }
        }while(i.month > 12);
        d->day = i.day;
        d->month = i.month;
        d->year = i.year;
}