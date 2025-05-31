#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa (int n, char s[], int min_width);
void reverse(char s[]);
void itob(int n, char s[], unsigned char b);

int main()
{
    int num = 992934;
    char str[100];

    itob(num, str, 16);
    printf("%s\n", str);

    itob(num, str, 8);
    printf("%s\n", str);

    itoa(num, str, 10);
    printf("%s\n", str);

    return 0;
}

void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa (int n, char s[], int min_width)
{
    int i, sign;

    if ((sign = n) < 0) /* сохраняем знак */
        n = -n; /* делаем n положительным */
    
    i = 0;

    do { /* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0'; /* следующая цифра */
    }
    while ((n /= 10) > 0); /* исключить ее */

    if (sign < 0)
        s[i++] = '-';

    int temp = strlen(s) - min_width;
    if (temp < 0)
    {
        for (; temp != 0; temp++)
        {
            s[i++] = ' ';
        }
    }
    
    s[i] = '\0';
    reverse(s);
}

void itob(int n, char s[], unsigned char b)
{
    char char_set[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int remainder = 0;
    int i = 0;

    for (; n != 0; n /= b)
    {
        remainder = n % b;
        s[i++] = char_set[remainder];
    }

    s[i] = '\0';

    reverse(s);
}