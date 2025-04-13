#include <stdio.h>

int main() {
    char words_array[5][25];
    int letters_array[26];
    for (size_t i = 0; i < (sizeof(words_array) / sizeof(words_array[0])); i++) {
        printf("Input word %d: ", i + 1);
        scanf("%24s", words_array[i]);
    }

    for (size_t i = 0; i < (sizeof(letters_array) / sizeof(letters_array[0])); i++)
    {
        letters_array[i] = 0;
    }
    

    for (size_t i = 0; i < (sizeof(words_array) / sizeof(words_array[0])); i++)
    {
        printf("%16s|", words_array[i]);
        for (size_t j = 0; words_array[i][j] != '\0'; j++)
        {
            printf("#");
            letters_array[words_array[i][j] - 'a']++;
        }
        printf("\n");
    }

    for (size_t i = 0; i < (sizeof(letters_array) / sizeof(letters_array[0])); i++)
    {
        printf("%c|", 'a' + i);
        for (size_t j = 0; j < letters_array[i]; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}