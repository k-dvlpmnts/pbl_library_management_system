#include "header.h"

int fine_check(struct date cd, struct date dd)
{
    if (cd.year < dd.year)
        return 1;
    else if (cd.year > dd.year)
        return 0;
    if (cd.month < dd.month)
        return 1;
    else if (cd.month > dd.month)
        return 0;
    if(cd.day <= dd.day)
        return 1;
    return 0;
}