#include <stdio.h>
#define MAXLINE 1000 /* максимальный размер вводимой строки */

int get_line(char s[], int lim);
void copy(char to[], char from[]);

/* печать самой длинной строки */
int main()
{
    int len; /* длина текущей строки */
    int max; /* длина максимальной из просмотренных строк */
    unsigned int i = 0;
    char line[MAXLINE]; /* текущая строка */
    char longest[MAXLINE]; /* самая длинная строка */
    char lines_array[100][MAXLINE];
    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0) 
    {
        if (line[len - 1] != '\n')
        {
            while(getchar() != '\n')
            {
                len++;
            }
        }
        
        if (len > max) {
        max = len;
        copy(longest, line);
        }

        if (len > 80)
        {
            copy(lines_array[i], line);
            i++;
        }
        
    }
    if (max > 0) {/* была ли хоть одна строка? */
    printf("%s With the length of %d", longest, max);
    }
    for (size_t j = 0; j <= i; j++)
    {
        printf("%s", lines_array[j]);
    }
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