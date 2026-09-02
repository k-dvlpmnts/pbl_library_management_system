#include "header.h"

int check_repeat(int cid, int cISBN)
{  
    struct issuedbooks i1;
    FILE *checkptr;
    checkptr = fopen("issued.txt", "r+");
    while(fscanf(checkptr, " %d, %[^,], %[^,], %d, %[^,], %d, %02d %02d %d, %02d %02d %d\n", &i1.iISBN, i1.ibookname, i1.iauthorname, &i1.ibookquant, i1.issuedto, &i1.id, &i1.issue.day, &i1.issue.month, &i1.issue.year, &i1.due.day, &i1.due.month, &i1.due.year) == 12)
    {
        if(cid == i1.id && cISBN == i1.iISBN)
            return 1;
    }
    return 0;
}