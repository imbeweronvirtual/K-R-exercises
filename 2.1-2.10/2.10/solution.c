#include <stdio.h>

#define STEP 32

char lower(char sym);

int main()
{
    char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        printf("%c", lower(str[i])); // output must be lowkey letters
    }
    
    printf("\n%c", lower('a')); // to make sure that func works properly, output must be the same letter

    return 0;
}

char lower(char sym)
{
    return (sym >= 65 && sym <= 90) ? sym + STEP : sym;
}