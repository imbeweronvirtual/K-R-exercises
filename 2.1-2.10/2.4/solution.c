#include <stdio.h>

int strsqueeze(char s1[], char s2[]);
int charsqueeze(char s[], char c);

int main()
{
    char first_str[] = "hello world";
    char second_str[] = "abcde";

    strsqueeze(first_str, second_str);

    printf("%s", first_str);

    return 0;
}

int strsqueeze(char s1[], char s2[])
{
    int i = 0;

    while (s2[i] != '\0')
    {
        charsqueeze(s1, s2[i]);
        i++;
    }
}

int charsqueeze(char s[], char c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
        {
            s[j++] = s[i];
        }        
    s[i] = '\0';
    s[j] = '\0';
}