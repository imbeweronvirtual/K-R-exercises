#include <stdio.h>
#include <string.h>

int main() {
    int numberOfStrings = 0;
    int resultOfScanning;

    while (1)
    {
        printf("Input: ");
        resultOfScanning = scanf("%d", &numberOfStrings);
        if (resultOfScanning != 1 || numberOfStrings < 1)
        {
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    for (size_t string = 1; string < numberOfStrings + 1; string++)
    {
        for (size_t i = 0; i < numberOfStrings - string; i++)
        {
            printf(" ");
        }
        for (size_t i = 0; i < string; i++)
        {
            printf("*");
        }

        printf("  ");
        
        for (size_t i = 0; i < string; i++)
        {
            printf("*");
        }
        
        printf("\n");
    }
    
    
    return 0;
}