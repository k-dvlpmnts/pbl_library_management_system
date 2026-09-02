#include "header.h"

void irefresh(int del_iISBN, int del_id)
{
    int i = 0, l;
    struct issuedbooks ri[total_calculator(2)];
    FILE *fp;
    fp = fopen("issued.txt", "r+");
    while (fscanf(fp, " %d, %[^,], %[^,], %d, %[^,], %d, %02d %02d %d, %02d %02d %d", &ri[i].iISBN, ri[i].ibookname, ri[i].iauthorname, &ri[i].ibookquant, ri[i].issuedto, &ri[i].id, &ri[i].issue.day, &ri[i].issue.month, &ri[i].issue.year, &ri[i].due.day, &ri[i].due.month, &ri[i].due.year) == 12)
    {
        i++;
    }
    fclose(fp);
    l = i;
    i = 0;
    fp = fopen("issued.txt", "w");
    while(i < l)
    {
        if(ri[i].id == del_id && del_iISBN == ri[i].iISBN)
        {
            i++;
            continue;
        }
        else
            fprintf(fp, "%d, %s, %s, %d, %s, %d, %02d %02d %d, %02d %02d %d\n", ri[i].iISBN, ri[i].ibookname, ri[i].iauthorname, ri[i].ibookquant, ri[i].issuedto, ri[i].id, ri[i].issue.day, ri[i].issue.month, ri[i].issue.year, ri[i].due.day, ri[i].due.month, ri[i].due.year);
        i++;
    }
    fclose(fp);
    return;
}