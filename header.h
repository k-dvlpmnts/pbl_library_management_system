#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define green "\x1b[32m"
#define blue "\x1b[34m"
#define red "\x1b[31m"
#define reset "\x1b[0m"

struct userdata
{
    char username[20];
    char password[20];
};
struct bookstock
{
    int ISBN;
    char bookname[20];
    char authorname[20];
    int bookquant;
};
struct date
{
    int day;
    int month;
    int year;
};
struct issuedbooks
{
    int iISBN;
    char ibookname[20];
    char iauthorname[20];
    int ibookquant;
    int id;
    char issuedto[20];
    struct date issue;
    struct date due;
};


void books(int);

int check_repeat(int, int);

void date_cal(struct date i, struct date *d);

int date_validate(struct date);

int fine_check(struct date, struct date);

void format(char *);

void irefresh(int, int);

int total_calculator(int);

void update_stock(int, int);

int userbase(char [], char [], int);

int validate(char []);
int uvalidate(char []);