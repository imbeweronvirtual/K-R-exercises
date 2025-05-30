#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa (int n, char s[]);
void reverse(char s[]);

int main()
{
    char str[20];
    int n = INT_MIN;
    itoa(n, str);
    printf("%s", str);
}

/* itoa: преобразование n в строку s */
void itoa (int n, char s[])
{
    int i, sign;
    long temp = (long)n;

    if ((sign = temp) < 0) /* сохраняем знак */
        temp = -temp; /* делаем temp положительным */

    i = 0;

    do { /* генерируем цифры в обратном порядке */
        s[i++] = temp % 10 + '0'; /* следующая цифра */
    } while ((temp /= 10) > 0); /* исключить ее */

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
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