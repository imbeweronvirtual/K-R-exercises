#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_LENGTH 100
#define MAX_STRING_LENGTH 1000

typedef struct
{
    char string[MAX_STRING_LENGTH];
    unsigned int str_length;
} String;

int compare(const void* a, const void* b);


int main()
{
    String strings_array[MAX_ARRAY_LENGTH];
    char c;
    short need_of_break = 0;
    size_t i;
    for (i = 0; i <= MAX_ARRAY_LENGTH; i++)
    {
        unsigned int length = 0;
        for (size_t j = 0; j < MAX_STRING_LENGTH; j++)
        {
            c = getchar();
            if (c == EOF)
            {
                need_of_break++;
                break;
            }
            length++;
            if (c == '\n')
            {
                strings_array[i].string[j] = c;
                strings_array[i].str_length = length;
                break;
            }
            
            strings_array[i].string[j] = c;
        }
        if (need_of_break)
        {
            break;
        }
    }
    
    unsigned int size = sizeof(strings_array) / sizeof(strings_array[0]);
    qsort(strings_array, i+1, sizeof(String), compare);

    for (size_t j = 0; j <= i; j++)
    {
        printf("%s", strings_array[j].string);
    }
    return 0;
}

int compare(const void* a, const void* b)
{
    return ((String*)a) -> str_length - ((String*)b) -> str_length;
}