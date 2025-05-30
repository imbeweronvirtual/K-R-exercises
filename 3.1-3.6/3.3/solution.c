#include <stdio.h>
#include <ctype.h>

int expand(char s1[], char s2[]);

int main()
{
    char f_str[] = "a-zA-Z0-90-36-8a-b-c";
    char s_str[100];

    expand(f_str, s_str);

    // output: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890123678abc
    printf("%s\n", s_str);

    return 0;
}

int expand(char s1[], char s2[])
{
    unsigned int i;
    unsigned int j = 0;
    char last_ch = 0;

    for (i = 0; isspace(s1[i]); i++)
        ;
    
    if (s1[i] == '-')
    {
        s2[j] = s1[i];
        i++;
    }
    

    for (; s1[i] != '\0'; i++)
    {
        if (s1[i] == '-')
        {
            continue;
        }

        if ((isdigit(s1[i]) || isalpha(s1[i])) && !last_ch)  
        {
            last_ch = s1[i];
            s2[j] = last_ch;
            j++;
        }
        else if (last_ch && isdigit(s1[i]) - isdigit(last_ch) == 0
        && isalpha(s1[i]) - isalpha(last_ch) == 0
        && isupper(s1[i]) - isupper(last_ch) == 0)
        {
            int ch_in_line = s1[i] - last_ch;

            for (int k = last_ch + 1; ch_in_line != 0; k++, ch_in_line--, j++)
            {
                s2[j] = k;
            }
            
            last_ch = 0;
        }
        else
        {
            s2[j] = s1[i];
            j++;
        }
    }
    s2[j] = '\0';
}