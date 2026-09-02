#include "header.h"

int total_calculator(int file)
{
    int i = 0;
    struct bookstock b1;
    struct issuedbooks i1;
    FILE *fi, *fb;
    if (file == 1)
    {
        fb = fopen("books.txt", "r");
        while(fscanf(fb, " %d, %[^,], %[^,], %d\n", &b1.ISBN, b1.bookname, b1.authorname, &b1.bookquant) == 4)
            i++;
        fclose(fb);
    }
    else
    {
        fi = fopen("issued.txt", "r");
        while(fscanf(fi, " %d, %[^,], %[^,], %d, %[^,], %d, %02d %02d %d, %02d %02d %d\n", &i1.iISBN, i1.ibookname, i1.iauthorname, &i1.ibookquant, i1.issuedto, &i1.id, &i1.issue.day, &i1.issue.month, &i1.issue.year, &i1.due.day, &i1.due.month, &i1.due.year) == 12)
            i++;
        fclose(fi);
    }
    return i;
}