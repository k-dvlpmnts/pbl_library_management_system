#include "header.h"

void books (int f2choice)
{
    int found = 0, newquant;
    int schoice1, schoice2;
    int sISBN, sid;
    int issuequant;
    char sbookname[20] = {'\0'};
    char sauthorname[20] = {'\0'};
    char sissuedto[20] = {'\0'};
    struct bookstock b1 = {.bookname = {'\0'}, .authorname = {'\0'}}, b2 = {.bookname = {'\0'}, .authorname = {'\0'}};
    struct issuedbooks i1 = {.ibookname = {'\0'}, .iauthorname = {'\0'}, .issuedto = {'\0'}};
    struct date s;
    char *search;
    time_t t;
    time(&t);
    struct tm *tp= localtime(&t);
    FILE *fptrbooks, *temp1, *temp2;
    FILE *fptrissued;

    switch (f2choice)
    {
        case 1:
        sstart:
        printf("\nSearch by:\n1.ISBN\n2.Bookname\n3.Authorname\n\nTo exit press 4\n\nEnter Choice: ");
        scanf(" %d", &schoice1);
        switch(schoice1)
        {
            case 1:
            found = 0;
            fptrbooks = fopen("books.txt", "r+");
            do{
                printf("\nEnter ISBN: ");
                scanf("%d", &sISBN);
                if (sISBN > 9999 || sISBN < 1000)
                    printf(red "\nInvalid\n" reset);
            }while(sISBN > 9999 || sISBN < 1000);
            while(fscanf(fptrbooks, " %d, %[^,], %[^,], %d\n", &b1.ISBN, b1.bookname, b1.authorname, &b1.bookquant) == 4)
            {
                if (b1.ISBN == sISBN)
                {
                    found = 1;
                    printf(blue "\nISBN: " green "%d" blue "\nBOOKNAME: " green "%s" blue "\nAUTHORNAME: " green "%s" blue "\nQUANTITY: " green "%d\n" reset, b1.ISBN, b1.bookname, b1.authorname, b1.bookquant);
                    if(b1.bookquant == 0)
                    {
                        printf(red "\nOut of Stock\n" reset);
                        goto sstart;
                    }
                    printf("\nTo Issue Press 1\nTo Search again press 2\nEnter Choice: ");
                    scanf("%d", &schoice2);
                    if (schoice2 == 1)
                    {
                        do{
                            printf("\nEnter Customer Name: ");
                            scanf(" %[^\n]", i1.issuedto);
                            if(validate(i1.issuedto) == 0)
                                printf(red "\nInvalid Input\n" reset);
                        }while (validate(i1.issuedto) == 0);
                        format(i1.issuedto);
                        do{
                            printf("\nEnter Customer ID: ");
                            scanf("%d", &i1.id);
                            if(i1.id < 1000 || i1.id > 9999)
                                printf(red "\nInvalid Input\n" reset);
                        }while(i1.id < 1000 || i1.id > 9999);
                        if (check_repeat(i1.id, b1.ISBN) == 1)
                        {
                            printf(red "\nAlready Issued\n" reset);
                            return;
                        }
                        /*i1.issue.day = tp->tm_mday;
                        i1.issue.month = tp->tm_mon + 1;
                        i1.issue.year = tp->tm_year + 1900;*/
                        do{
                            printf("\nEnter Issue date: ");
                            scanf("%d %d %d", &i1.issue.day, &i1.issue.month, &i1.issue.year);
                            if (date_validate(i1.issue) == 0)
                                printf(red "\nInvalid Date\n" reset);
                        }while(date_validate(i1.issue) == 0);

                        date_cal(i1.issue, &i1.due);
                        printf("\nDUE DATE: %02d-%02d-%02d\n", i1.due.day, i1.due.month, i1.due.year);

                        fptrissued = fopen("issued.txt", "a+");
                        fprintf(fptrissued, "%d, %s, %s, %d, %s, %d, %02d %02d %d, %02d %02d %d\n", b1.ISBN, b1.bookname, b1.authorname, 1, i1.issuedto, i1.id, i1.issue.day, i1.issue.month, i1.issue.year, i1.due.day, i1.due.month, i1.due.year);
                        fclose(fptrissued);
                        printf(green "\nIssued\n" reset);

                        fclose(fptrbooks);

                        update_stock(b1.ISBN, 1);

                        break;
                    }
                    else if (schoice2 == 2)
                        goto sstart;
                    else
                    {
                        printf("\nInvalid choice\n");
                        goto sstart;
                    }
                }
            }
            if (found == 0)
            {
                printf(red "\nNot found" reset "\nSearch again\n");
                goto sstart;
            }
            return;

            case 2:
            found = 0;
            fptrbooks = fopen("books.txt", "r+");
            do{
                printf("\nEnter Bookname: ");
                scanf(" %[^\n]", sbookname);
                if(validate(sbookname) == 0)
                    printf(red "\nInvalid Input\n" reset);
            }while(validate(sbookname) == 0);
            format(sbookname);
            while(fscanf(fptrbooks, " %d, %[^,], %[^,], %d\n", &b1.ISBN, b1.bookname, b1.authorname, &b1.bookquant) == 4)
            {
                search = strstr(b1.bookname, sbookname);
                if (search != NULL)
                {
                    found = 1;
                    printf(blue "\nISBN: " green "%d" blue "\nBOOKNAME: " green "%s" blue "\nAUTHORNAME: " green "%s" blue "\nQUANTITY: " green "%d\n" reset, b1.ISBN, b1.bookname, b1.authorname, b1.bookquant);
                    if(b1.bookquant == 0)
                    {
                        printf(red "\nOut of Stock\n" reset "\nNext Match: \n");
                        schoice2 = 2;
                    }
                    else
                    {
                        printf("\nTo Issue Press 1\nTo show next match press 2\nTo Search again press 3\nEnter Choice: ");
                        scanf("%d", &schoice2);
                    }
                    if (schoice2 == 1)
                    {
                        do{
                            printf("\nEnter Customer Name: ");
                            scanf(" %[^\n]", i1.issuedto);
                            if(validate(i1.issuedto) == 0)
                                printf(red "\nInvalid Input\n" reset);
                        }while (validate(i1.issuedto) == 0);
                        format(i1.issuedto);
                        do{
                            printf("\nEnter Customer ID: ");
                            scanf("%d", &i1.id);
                            if(i1.id < 1000 || i1.id > 9999)
                                printf(red "\nInvalid Input\n" reset);
                        }while(i1.id < 1000 || i1.id > 9999);
                        if (check_repeat(i1.id, b1.ISBN) == 1)
                        {
                            printf(red "\nAlready Issued\n" reset);
                            return;
                        }
                        /*i1.issue.day = tp->tm_mday;
                        i1.issue.month = tp->tm_mon + 1;
                        i1.issue.year = tp->tm_year + 1900;*/
                        do{
                            printf("\nEnter Issue date: ");
                            scanf("%d %d %d", &i1.issue.day, &i1.issue.month, &i1.issue.year);
                            if (date_validate(i1.issue) == 0)
                                printf(red "\nInvalid Date\n" reset);
                        }while(date_validate(i1.issue) == 0);
                        
                        date_cal(i1.issue, &i1.due);
                        printf("\nDUE DATE: %02d-%02d-%02d\n", i1.due.day, i1.due.month, i1.due.year);

                        fptrissued = fopen("issued.txt", "a+");
                        fprintf(fptrissued, "%d, %s, %s, %d, %s, %d, %02d %02d %d, %02d %02d %d\n", b1.ISBN, b1.bookname, b1.authorname, 1, i1.issuedto, i1.id, i1.issue.day, i1.issue.month, i1.issue.year, i1.due.day, i1.due.month, i1.due.year);
                        fclose(fptrissued);
                        printf(green "\nIssued\n" reset);

                        fclose(fptrbooks);

                        update_stock(b1.ISBN, 1);

                        break;
                    }
                    else if (schoice2 == 2)
                        continue;
                    else if (schoice2 == 3)
                        goto sstart;
                    else
                    {
                        printf(red "\nInvalid choice\n" reset);
                        goto sstart;
                    }
                    break;
                }
            }
            if (found == 0)
            {
                printf(red "\nNot found" reset "\nSearch again\n");
                goto sstart;
            }
            return;

            case 3:
            found = 0;
            fptrbooks = fopen("books.txt", "r+");
            do{
                printf("\nEnter Authorname: ");
                scanf(" %[^\n]", sauthorname);
                if(validate(sauthorname) == 0)
                    printf(red "\nInvalid Input\n" reset);
            }while(validate(sauthorname) == 0);
            format(sauthorname);
            while(fscanf(fptrbooks, " %d, %[^,], %[^,], %d\n", &b1.ISBN, b1.bookname, b1.authorname, &b1.bookquant) == 4)
            {
                search = strstr(b1.authorname, sauthorname);
                if (search != NULL)
                {
                    found = 1;
                    printf(blue "\nISBN: " green "%d" blue "\nBOOKNAME: " green "%s" blue "\nAUTHORNAME: " green "%s" blue "\nQUANTITY: " green "%d\n" reset, b1.ISBN, b1.bookname, b1.authorname, b1.bookquant);
                    if(b1.bookquant == 0)
                    {
                        printf(red "\nOut of Stock\n" reset "\nNext Match: \n");
                        schoice2 = 2;
                    }
                    else
                    {
                        printf("\nTo Issue Press 1\nTo show next match press 2\nTo Search again press 3\nEnter Choice: ");
                        scanf("%d", &schoice2);
                    }
                    if (schoice2 == 1)
                    {
                        do{
                            printf("\nEnter Customer Name: ");
                            scanf(" %[^\n]", i1.issuedto);
                            if(validate(i1.issuedto) == 0)
                                printf(red "\nInvalid Input\n" reset);
                        }while (validate(i1.issuedto) == 0);
                        format(i1.issuedto);
                        do{
                            printf("\nEnter Customer ID: ");
                            scanf("%d", &i1.id);
                            if(i1.id < 1000 || i1.id > 9999)
                                printf(red "\nInvalid Input\n" reset);
                        }while(i1.id < 1000 || i1.id > 9999);
                        if (check_repeat(i1.id, b1.ISBN) == 1)
                        {
                            printf(red "\nAlready Issued\n" reset);
                            return;
                        }

                        /*i1.issue.day = tp->tm_mday;
                        i1.issue.month = tp->tm_mon + 1;
                        i1.issue.year = tp->tm_year + 1900;*/
                        do{
                            printf("\nEnter Issue date: ");
                            scanf(" %d %d %d", &i1.issue.day, &i1.issue.month, &i1.issue.year);
                            if (date_validate(i1.issue) == 0)
                                printf(red "\nInvalid Date\n" reset);
                        }while(date_validate(i1.issue) == 0);
                        
                        date_cal(i1.issue, &i1.due);
                        printf("\nDUE DATE: %02d-%02d-%02d\n", i1.due.day, i1.due.month, i1.due.year);

                        fptrissued = fopen("issued.txt", "a+");
                        fprintf(fptrissued, "%d, %s, %s, %d, %s, %d, %02d %02d %d, %02d %02d %d\n", b1.ISBN, b1.bookname, b1.authorname, 1, i1.issuedto, i1.id, i1.issue.day, i1.issue.month, i1.issue.year, i1.due.day, i1.due.month, i1.due.year);
                        fclose(fptrissued);
                        printf(green "\nIssued\n" reset);

                        fclose(fptrbooks);

                        update_stock(b1.ISBN, 1);

                        break;
                    }
                    else if (schoice2 == 2)
                        continue;
                    else if (schoice2 == 3)
                        goto sstart;
                    else
                    {
                        printf(red "\nInvalid choice\n" reset);
                        goto sstart;
                    }
                    break;
                }
            }
            if (found == 0)
            {
                printf(red "\nNot found" reset "\nSearch again\n");
                goto sstart;
            }
            return;

            case 4:
            return;

            default:
            printf(red "\nInvalid choice" reset "\nEnter again\n");
            goto sstart;
        }
        break;

        case 2:
        rstart:
        found = 0;
        fptrissued = fopen("issued.txt", "r+");
        do{
            printf("\nEnter Customer ID: ");
            scanf("%d", &sid);
            if(sid < 1000 || sid > 9999)
                printf(red "\nInvalid Input\n" reset);
        }while(sid < 1000 || sid > 9999);
        do{
            printf("\nEnter ISBN: ");
            scanf("%d", &sISBN);
            if (sISBN > 9999 || sISBN < 1000)
                printf(red "\nInvalid\n" reset);
        }while(sISBN > 9999 || sISBN < 1000);
        while(fscanf(fptrissued, " %d, %[^,], %[^,], %d, %[^,], %d, %02d %02d %d, %02d %02d %d\n", &i1.iISBN, i1.ibookname, i1.iauthorname, &i1.ibookquant, i1.issuedto, &i1.id, &i1.issue.day, &i1.issue.month, &i1.issue.year, &i1.due.day, &i1.due.month, &i1.due.year) == 12)
        {
            if ((i1.iISBN == sISBN) && (sid == i1.id))
            {
                found = 1;
                printf(blue "\nISBN: " green"%d" blue"\nBOOKNAME: " green "%s" blue "\nAUTHOR NAME: " green "%s" blue "\nQUANTITY: " green "%d" blue "\nCUSTOMER NAME: " green "%s" blue "\nCUSTOMER ID: " green "%d" blue "\nISSUE DATE: " green "%02d-%02d-%d" blue "\nDUE DATE: " green "%02d-%02d-%d\n" reset, i1.iISBN, i1.ibookname, i1.iauthorname, i1.ibookquant, i1.issuedto, i1.id, i1.issue.day, i1.issue.month, i1.issue.year, i1.due.day, i1.due.month, i1.due.year);
                printf("\nTo Return Press 1\nTo Search again press 2\nEnter Choice: ");
                scanf("%d", &schoice2);
                if (schoice2 == 1)
                {
                    s.day = tp->tm_mday;
                    s.month = tp->tm_mon + 1;
                    s.year = tp->tm_year + 1900;

                    /*do{
                        printf("\nEnter Date: ");
                        scanf("%d %d %d", &s.day, &s.month, &s.year);
                        if (date_validate(s) == 0)
                            printf("\nInvalid Date\n");
                    }while(date_validate(s) == 0);*/

                    if(fine_check(s, i1.due) == 0)
                        printf(red "\nFine: Rs.20\n" reset);
                    update_stock(i1.iISBN, 0);
                    irefresh(i1.iISBN, i1.id);
                    printf(green "\nReturned\n" reset);
                    break;
                }
                else if (schoice2 == 2)
                    goto rstart;
                else
                {
                    printf(red "\nInvalid choice\n" reset);
                    goto rstart;
                }
            }
        }
        if (found == 0)
            printf(red "\nNot found" reset);
        return;

        case 3:
        do{
            printf("\nEnter book name: ");
            scanf(" %[^\n]", b1.bookname);
            if(validate(b1.bookname) == 0)
                printf(red "\nInvalid Input\n" reset);
        }while(validate(b1.bookname) == 0);
        format(b1.bookname);
        do{
            printf("\nEnter ISBN: ");
            scanf("%d", &b1.ISBN);
            if (b1.ISBN > 9999 || b1.ISBN < 1000)
                printf(red "\nInvalid\n" reset);
        }while(b1.ISBN > 9999 || b1.ISBN < 1000);
        do{
            printf("\nEnter Authorname: ");
            scanf(" %[^\n]", b1.authorname);
            if(validate(b1.authorname) == 0)
                printf(red "\nInvalid Input\n" reset);
        }while(validate(b1.authorname) == 0);
        format(b1.authorname);
        do{
            printf("\nEnter quantity: ");
            scanf(" %d", &b1.bookquant);
            if (b1.bookquant < 1)
                printf(red "\nInvalid Input\n" reset);
        }while (b1.bookquant < 1);

        fptrbooks = fopen("books.txt", "a+");
        fprintf(fptrbooks, "%d, %s, %s, %d\n", b1.ISBN, b1.bookname, b1.authorname, b1.bookquant);
        fclose(fptrbooks);

        printf(green "\nAdded\n" reset);
        return;

        case 4:
        found = 0;
        do{
            printf("\nEnter CUSTOMER ID: ");
            scanf("%d", &sid);
            if(sid < 1000 || sid > 9999)
                printf(red "\nInvalid Input\n" reset);
        }while(sid < 1000 || sid > 9999);
        fptrissued = fopen("issued.txt", "r");
        printf(blue "\n%-19s%-15s%-19s%-6s%-12s%-12s\n\n" reset, "ISSUED TO", "CUSTOMER ID", "BOOKNAME", "ISBN", "ISSUE DATE", "DUE DATE");
        while (fscanf(fptrissued, " %d, %[^,], %[^,], %d, %[^,], %d, %02d %02d %d, %02d %02d %d\n", &i1.iISBN, i1.ibookname, i1.iauthorname, &i1.ibookquant, i1.issuedto, &i1.id, &i1.issue.day, &i1.issue.month, &i1.issue.year, &i1.due.day, &i1.due.month, &i1.due.year) == 12)
        {
            found = 1;
            if (sid == i1.id)
                printf(green "%-19s%-15d%-19s%-6d%02d-%02d-%-6d%02d-%02d-%-6d\n" reset, i1.issuedto, i1.id, i1.ibookname, i1.iISBN, i1.issue.day, i1.issue.month, i1.issue.year, i1.due.day, i1.due.month, i1.due.year);
        }
        if (found = 0)
            printf(red "\nNot Found\n" reset);
        fclose(fptrissued);
        return;

        case 5:
        found = 0;
        fptrbooks = fopen("books.txt", "r+");
        do{
            printf("\nEnter ISBN: ");
            scanf("%d", &sISBN);
            if (sISBN > 9999 || sISBN < 1000)
                printf(red "\nInvalid\n" reset);
        }while(sISBN > 9999 || sISBN < 1000);
        while(fscanf(fptrbooks, " %d, %[^,], %[^,], %d\n", &b1.ISBN, b1.bookname, b1.authorname, &b1.bookquant) == 4)
        {
            if (b1.ISBN == sISBN)
            {
                found = 1;
                do{
                    printf("\nEnter quantity: ");
                    scanf(" %d", &newquant);
                    if (newquant < 1)
                        printf(red "\nInvalid Input\n" reset);
                }while (newquant < 1);
                if(newquant == 1)
                    update_stock(b1.ISBN, 0);
                else
                    update_stock(b1.ISBN, newquant);
                printf(green "\nAdded\n" reset);
                break;
            }
        }
        if (found = 0)
            printf(red "\nNot Found\n" reset);
        fclose(fptrbooks);
        return;

        case 6:
        fptrbooks = fopen("books.txt", "r");
        fptrissued = fopen("issued.txt", "r");
        do{
            printf("\n1.Show Full Stock\n2.Show Specific\n3.Exit\nEnter Choice: ");
            scanf("%d", &schoice1);
            if(!(schoice1 == 1 || schoice1 == 2  || schoice1 == 3))
                printf(red "\nInvalid Input\n" reset);
        }while(!(schoice1 == 1 || schoice1 == 2  || schoice1 == 3));
        if(schoice1 == 3)
        {
            fclose(fptrbooks);
            fclose(fptrissued);
            return;
        }
        
        if(schoice1 == 1)
        {
            printf(blue "\n%-8s%-20s%-20s%-20s%-20s%-20s\n\n" reset, "ISBN", "BOOKNAME", "AUTHORNAME", "TOTAL QUANTITY", "CURRENT QUANTITY", "ISSUED QUANTITY");
            while(fscanf(fptrbooks, " %d, %[^,], %[^,], %d\n", &b1.ISBN, b1.bookname, b1.authorname, &b1.bookquant) == 4)
            {
                issuequant = 0;
                while (fscanf(fptrissued, " %d, %[^,], %[^,], %d, %[^,], %d, %02d %02d %d, %02d %02d %d\n", &i1.iISBN, i1.ibookname, i1.iauthorname, &i1.ibookquant, i1.issuedto, &i1.id, &i1.issue.day, &i1.issue.month, &i1.issue.year, &i1.due.day, &i1.due.month, &i1.due.year) == 12)
                    if(i1.iISBN == b1.ISBN)
                        issuequant++;
                printf(green "%-8d%-20s%-20s%-20d%-20d%-20d\n" reset, b1.ISBN, b1.bookname, b1.authorname, b1.bookquant + issuequant, b1.bookquant, issuequant);
                rewind(fptrissued);
            }
        }
        else if (schoice1 == 2)
        {
            do{
                printf("\nEnter ISBN: ");
                scanf("%d", &sISBN);
                if (sISBN > 9999 || sISBN < 1000)
                    printf(red "\nInvalid\n" reset);
            }while(sISBN > 9999 || sISBN < 1000);
            printf(blue "\n%-8s%-20s%-20s%-20s%-20s%-20s\n\n" reset, "ISBN", "BOOKNAME", "AUTHORNAME", "TOTAL QUANTITY", "CURRENT QUANTITY", "ISSUED QUANTITY");
            while(fscanf(fptrbooks, " %d, %[^,], %[^,], %d\n", &b1.ISBN, b1.bookname, b1.authorname, &b1.bookquant) == 4)
            {
                if(b1.ISBN == sISBN)
                {
                    issuequant = 0;
                    while (fscanf(fptrissued, " %d, %[^,], %[^,], %d, %[^,], %d, %02d %02d %d, %02d %02d %d\n", &i1.iISBN, i1.ibookname, i1.iauthorname, &i1.ibookquant, i1.issuedto, &i1.id, &i1.issue.day, &i1.issue.month, &i1.issue.year, &i1.due.day, &i1.due.month, &i1.due.year) == 12)
                        if(i1.iISBN == b1.ISBN)
                            issuequant++;
                    printf(green "%-8d%-20s%-20s%-20d%-20d%-20d\n" reset, b1.ISBN, b1.bookname, b1.authorname, b1.bookquant + issuequant, b1.bookquant, issuequant);
                    rewind(fptrissued);
                }
            }
        }

        fclose(fptrbooks);
        fclose(fptrissued);
        return;
    }
}