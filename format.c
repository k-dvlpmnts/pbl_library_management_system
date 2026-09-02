#include "header.h"

void format(char *str_format)
{
    int i, j, l;
    l = strlen(str_format) + 1;
    char str_new[l] = {};
    for (i = 0, j = 0; str_format[i] != 0; i++)
    {
        if (((str_format[i] >= 'A' && str_format[i] <= 'Z') || (str_format[i] >= 'a' && str_format[i] <= 'z')) && j == 0)
        {
            str_new[j] = toupper(str_format[i]);
            j++;
        }
        else if ((str_format[i] >= 'A' && str_format[i] <= 'Z') || (str_format[i] >= 'a' && str_format[i] <= 'z'))
        {
            str_new[j] = tolower(str_format[i]);
            j++;
        }
        else if (str_format[i] == ' ' && ((str_format[i+1] >= 'A' && str_format[i+1] <= 'Z') || (str_format[i+1] >= 'a' && str_format[i+1] <= 'z')))
        {
            str_new[j] = ' ';
            j++;
            i++;
            str_new[j] = toupper(str_format[i]);
            j++;
        }
    }
    str_new[j] = '\0';
    strcpy(str_format, str_new);
    return;
}