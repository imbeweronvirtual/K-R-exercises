#include <stdio.h>
#include <string.h>
#define MAXLINE 1000 /* максимальный размер вводимой строки */

int get_line(char s[], int lim);
void copy(char to[], char from[]);
void reverse(char to[], char from[]);
void delete_spaces(char to[],char from[]);

/* печать самой длинной строки */
int main()
{
    char string_array[100][1000];
    char term[1000];
    unsigned int i = 0;
    while (get_line(term, MAXLINE) > 0)
    {
        delete_spaces(string_array[i],term);
        i++;
    }
    for (size_t j = 0; j < i; j++)
    {
        printf("%s\n",string_array[j]);
    }
    reverse(term,string_array[0]);
    printf("%s\n",term);
    return 0;
}

/* getline: читает строку в s, возвращает длину */
int get_line(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
/* copy: копирует из 'from' в 'to'; to достаточно большой */
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
    ++i;
}

void reverse(char to[], char from[]) 
{
    int i;
    unsigned int j;
    i = 0;
    j = 0;
    for (; from[i] != 0 && from[i] != 10; i++)
    {
        ;
    }
    while (i >= 0)
    {
        to[j] = from[i];
        i--;
        j++;
    }
    to[j + 1] = '\0';
}

void delete_spaces(char to[],char from[])
{
    char last_letter;
    char now_letter;
    for (size_t i = 0, j = 0; from[i] != 0; i++)
    {
        now_letter = from[i];
        if (now_letter == ' ' && last_letter == ' ' || now_letter == '\t' && last_letter == '\t')
        {
            continue;
        }
        to[j] = from[i];
        last_letter = now_letter;
        j++;
    }
    
}