#include <stdio.h>

int escape(char s[], char t[]);
int reverse_escape(char s[], char t[]);

int main()
{
    char str[] = "Hello,\nworld,\tis this compiling?";
    char dest[33];

    escape(dest, str);
    printf("%s\n", dest);

    reverse_escape(str, dest);
    printf("%s\n", str);
}

int escape(char s[], char t[])
{
    int i = 0;
    for (int j = 0; t[j] != '\0'; j++)
    {
        switch (t[j])
        {
        case '\n':
            s[i] = '\\';
            s[++i] = 'n';
            ++i;
            break;
        case '\t':
            s[i] = '\\';
            s[++i] = 't';
            ++i;
            break;
        default:
            s[i] = t[j];
            ++i;
            break;
        }
    }
    s[i] = '\0';

    return 0;
}

int reverse_escape(char s[], char t[])
{
    int i = 0;
    
    for (size_t j = 0; t[j] != '\0'; j++)
    {
        if (t[j] == '\\')
        {
            switch (t[j + 1])
            {
            case 'n':
                s[i] = '\n';
                ++i;
                ++t;
                break;
            case 't':
                s[i] = '\t';
                ++i;
                ++t;
                break;
            default:
                s[i] = t[j];
                ++i;
                break;
            }
        } else
        {
            s[i] = t[j];
            ++i;
        }
    }

    s[i] = '\0';

    return 0;
}