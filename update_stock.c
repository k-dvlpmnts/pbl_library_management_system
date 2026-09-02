#include "header.h"

void update_stock(int uISBN, int call)
{
    int i = 0, l;
    FILE *fptrupdate;
    struct bookstock ub[total_calculator(1)];
    fptrupdate = fopen("books.txt", "r+");
    while(fscanf(fptrupdate , " %d, %[^,], %[^,], %d\n", &ub[i].ISBN, ub[i].bookname, ub[i].authorname, &ub[i].bookquant) == 4)
    {
        i++;
    }
    fclose(fptrupdate);

    fptrupdate = fopen("books.txt", "w");

    l = i;
    i = 0;

    while(i < l)
    {
        if (ub[i].ISBN == uISBN)
        {
            if (call == 1)
                ub[i].bookquant--;
            else if (call == 0)
                ub[i].bookquant++;
            else
                ub[i].bookquant += call;
            fprintf(fptrupdate, "%d, %s, %s, %d\n", ub[i].ISBN, ub[i].bookname, ub[i].authorname, ub[i].bookquant);
        }
        else
            fprintf(fptrupdate, "%d, %s, %s, %d\n", ub[i].ISBN, ub[i].bookname, ub[i].authorname, ub[i].bookquant);
        i++;
    }
    fclose(fptrupdate);
    return;
}