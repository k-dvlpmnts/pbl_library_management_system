#include "header.h"

int validate(char arr_check[])
{
    int i;
    for (i = 0; arr_check[i] != '\0'; i++)
    {
        if((arr_check[i] >= 'a' && arr_check[i] <= 'z') || (arr_check[i] >= 'A' && arr_check[i] <= 'Z') || arr_check[i] == ' ')
            continue;
        else
            return 0;
    }
    return 1;
}

int uvalidate(char str_check[])
{
    int i;
    for (i = 0; str_check[i] != '\0'; i++)
        if (str_check[i] == ' ')
            return 0;
    return 1;
}