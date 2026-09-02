#include "header.h"

void main()
{
    char username[20] = {'\0'}, pass[20] = {'\0'};
    int  c, choice;
    printf("\n*****LIBRARY*****\n");
    start:
    c = 0;
    while (c < 3)
    {
        printf("\n   LOGIN\nUsername: ");
        scanf(" %[^\n]", username);
        printf("Password: ");
        scanf(" %[^\n]", pass);
        if (userbase(username, pass, 1) == 1)
            break;
        else
            printf(red "\nIncorrect Username or Password\n\n%d attempts left\n" reset, 2-c);
        c++;
    }
    if (c == 3)
        exit(0);
    if(strcmp(username, "admin") == 0)
        do{
            printf("\n1.Issue Book\n2.Return Book\n3.Add New Book\n4.Show Issued Books\n5.Add Copies\n6.Show Stock Details\n7.Add User\n8.Change Password\n9.Logout\nEnter Choice:");
            scanf("%d", &choice);
            switch (choice)
            {
                case 1:
                books(1);
                break;
                case 2:
                books(2);
                break;
                case 3:
                books(3);
                break;
                case 4:
                books(4);
                break;
                case 5:
                books(5);
                break;
                case 6:
                books(6);
                break;
                case 7:
                userbase(username, pass, 2);
                break;
                case 8:
                userbase(username, pass, 3);
                break;
                case 9:
                goto start;
                break;
                default:
                printf(red "\nInvalid Input!\n" reset);
            }
        }while (1);

    else
        do{
            printf("\n1.Issue Book\n2.Return Book\n3.Show Issued Books\n4.Change Password\n5.Logout\nEnter Choice:");
            scanf("%d", &choice);
            switch (choice)
            {
                case 1:
                books(1);
                break;
                case 2:
                books(2);
                break;
                case 3:
                books(4);
                break;
                case 4:
                userbase(username, pass, 3);
                break;
                case 5:
                goto start;
                break;             
                default:
                printf(red "\nInvalid Input!\n" reset);
            }
        }while (1);
}