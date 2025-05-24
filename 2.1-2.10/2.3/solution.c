#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef int ErrorCode;

ErrorCode htoi(char num[], int *to);

int main()
{
    char hex_num[23];
    int result = 0;

    while (1)
    {
        printf("Print the signed hexademical number that you want to transform, starting with 0x or 0X, 32bit long: ");

        if (fgets(hex_num, sizeof(hex_num), stdin) != NULL)
        {
            if (htoi(hex_num, &result) == 0)
            {
                printf("%d is signed decimal int representation\n", result);
                break;
            }
        }
    }

    return 0;
}

ErrorCode htoi(char num[], int *to)
{
    unsigned short end_of_string_inx;
    unsigned short str_length;

    if ((str_length = strcspn(num, "\n\0")) != 10)
    {
        printf("The format is not hexademical integer\n");
        return 1;
    }
    
    num[str_length] = '\0';

    for (int i = 0; i < str_length; i++)
    {
        num[i] = toupper(num[i]);
        if (i >= 2)
        {
            if (!isdigit(num[i]) && num[i] < 65 || num[i] > 70)
            {
                printf("Wrong format on %d position\n", i + 1);

                return 1;
            }
        } 
    }
    
    if (strncmp("0X", num, 2) != 0)
    {
        printf("The format is not hexademical\n");
    }
    
    long acc = 0;
    unsigned short power = 0;

    for (int i = strlen(num) - 1; i >= 2; i--)
    {
        if (isalpha(num[i]))
        {
            acc += (num[i] - 55) * (long)pow(16, power);
            power++;
        }
        else
        {
            acc += (num[i] - '0') * (long)pow(16, power);
            power++;
        }
    }

    if ((1U << 31) & acc)
    {
        acc -= (1L << 32);
    }

    *to = (int)acc;

    return 0;
}