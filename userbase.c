#include "header.h"

int userbase(char fusername[], char fpass[], int f1choice)
{
    char newuser[20] = {'\0'}, newpass[20] = {'\0'};
    int i = 0, duplicate = 1, c, flag = 0, ind, l;
    FILE *fptruser;
    
    struct userdata user;
    
    switch (f1choice)
    {
        case 1:
        fptruser = fopen ("userdata.txt", "r");
        while (fscanf(fptruser, " %[^,], %s", user.username, user.password) == 2)
        {
            if ((strcmp (fusername, user.username) == 0) && (strcmp (fpass, user.password) == 0))
                return 1;
        }
        fclose(fptruser);
        return 0;

        case 2:
        while (duplicate)
        {
            do{
                printf("\nEnter Username to be added (Maximum 10 characters without space): ");
                scanf(" %[^\n]", newuser);
                if(strlen(newuser) > 10)
                    printf(red "\nLimit Exceeded\n" reset);
                if (uvalidate(newuser) == 0)
                    printf(red "\nSpace not allowed\n" reset);
            }while (strlen(newuser) > 10 || uvalidate(newuser) == 0);
            i = 0;
            fptruser = fopen ("userdata.txt", "r+");
            while (fscanf(fptruser, " %[^,], %s", user.username, user.password) == 2)
            {
                if (strcmp (newuser, user.username) == 0)
                {
                    duplicate = 1;
                    break;
                }
                else
                    duplicate = 0;
                i++;
            }
            fclose(fptruser);
            if (duplicate)
            {
                printf(red "\nUser already exist" reset "\nTo retry press 1\nTo exit press 2\n");
                do{
                    scanf("%d", &c);
                    if (c == 2)
                        return 2;
                    if (c != 1)
                        printf(red "\nInvalid Choice" reset "\nEnter Again:");
                }while (c != 1);
            }
            else
            {
                do{
                    printf("\nEnter Password (Maximum 10 characters wihout space): ");
                    scanf(" %[^\n]", newpass);
                    if(strlen(newpass) > 10)
                        printf(red "\nLimit exceeded\n" reset);
                    if(uvalidate(newpass) == 0)
                        printf(red "\nSpace not allowed\n" reset);
                }while (strlen(newpass) > 10 || uvalidate(newpass) == 0);
            }
            fptruser = fopen ("userdata.txt", "a+");
            fprintf(fptruser, "%s, %s\n", newuser, newpass);
            fclose(fptruser);
        }
        printf(green "\nUser Added\n" reset);
        return 2;

        case 3:
        struct userdata passchange[20];
        do{
            printf("\nEnter New Password(Maximum 10 characters without space): ");
            scanf(" %[^\n]", newpass);
            if(strlen(newpass) > 10)
                printf(red "\nLimit exceeded\n" reset);
            if(uvalidate(newpass) == 0)
                printf(red "\nSpace not allowed\n" reset);
        }while(strlen(newpass) > 10 || uvalidate(newpass) == 0);
        i = 0;
        fptruser = fopen ("userdata.txt", "r");
        while (fscanf(fptruser, " %[^,], %s", passchange[i].username, passchange[i].password) == 2)
        {
            if ((strcmp (fusername, passchange[i].username) == 0) && (strcmp (fpass, passchange[i].password) == 0))
            {
                flag = 1;
                ind = i;
            }
            i++;
        }
        fclose(fptruser);
        l = i;
        strcpy(passchange[ind].password, newpass);
        i = 0;
        if (flag)
        {
            fptruser = fopen ("userdata.txt", "w");
            while(i < l)
            {
                fprintf(fptruser, "%s, %s\n", passchange[i].username, passchange[i].password);
                i++;
            }
            fclose(fptruser);
        }
        printf(green "\nPassword Changed\n" reset);
    }
    return 2;
}