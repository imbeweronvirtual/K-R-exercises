#include <stdio.h>

int digitToString(void *source, char destination[], size_t destSize, char typeOfNumber)
{
    int resultOfTransform;
    if (typeOfNumber == 'l')
    {
        resultOfTransform = snprintf(destination, destSize, "%ld", *(long *)source);
    }
    else if (typeOfNumber == 'i')
    {
        resultOfTransform = snprintf(destination, destSize, "%d", *(int *)source);
    } else {
        printf("INVALID\n");
        return 0;
    }

    if (resultOfTransform < 0 || resultOfTransform >= destSize)
    {
        printf("INVALID\n");
        return 0;
    }
    else
    {
        return resultOfTransform;
    }
    return 0;
}


int main()
{
    long cardToCheck;
    int resultOfCheck;
    char term;
    char stringCardNumber[17];
    while (1)
    {
        printf("Please input: ");
        resultOfCheck = scanf("%ld%c", &cardToCheck, &term);
        if (resultOfCheck != 2 || term != '\n')
            {
                while (getchar() != '\n')
                    ;

                continue;
            }
            break;
    }

    if ((resultOfCheck = digitToString(&cardToCheck, stringCardNumber, 17, 'l')) == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    int digitsAddition;

    for (int i = resultOfCheck - 2; i >= 0; i -= 2)
    {
        int digit = (stringCardNumber[i] - '0') * 2;

        if (digit > 9)
        {
            char stringifyedDigits[3];
            digitToString(&digit, stringifyedDigits, 3, 'i');
            for (unsigned int index = 0; stringifyedDigits[index] != '\0'; index++)
            {
                digitsAddition += (stringifyedDigits[index] - '0');
            }
            continue;
        }
        digitsAddition += digit;
    }

    for (int i = resultOfCheck - 1; i >= 0; i -= 2)
    {
        int digit = stringCardNumber[i] - '0';
        digitsAddition = digitsAddition + digit;
    }

    if ((digitsAddition % 10) == 0)
    {
        if ((stringCardNumber[0] - '0' == 3) && resultOfCheck == 15)
        {
            printf("AMEX\n");
            return 0;
        }
        if (((stringCardNumber[0] - '0' == 4) && resultOfCheck == 15) || ((stringCardNumber[0] - '0' == 4) && resultOfCheck == 13))
        {
            printf("VISA\n");
            return 0;
        }
        if ((stringCardNumber[0] - '0' == 5) && resultOfCheck == 16)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        printf("INVALID\n");
        return 0;
    }

    printf("INVALID\n");
    return 0;
}