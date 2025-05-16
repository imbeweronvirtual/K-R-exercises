#include <stdio.h>
#include <ctype.h>

int main()
{
    unsigned int w_score[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    char f_word[1000];
    char s_word[1000];
    unsigned short f_word_iter = 0;
    unsigned short s_word_iter = 0;
    unsigned int f_word_acc = 0;
    unsigned int s_word_acc = 0;

    printf("Player 1: ");
    for (; f_word_iter < 1000 && (f_word[f_word_iter] = getchar()) != '\n'; f_word_iter++)
        ;

    printf("Player 2: ");
    for (; s_word_iter < 1000 && (s_word[s_word_iter] = getchar()) != '\n'; s_word_iter++)
        ;
    
    for (size_t i = 0; i < f_word_iter; i++)
    {
        if (!isalpha(f_word[i]))
        {
            continue;
        }

        f_word_acc = f_word_acc + w_score[toupper(f_word[i]) - 'A'];
    }

    for (size_t i = 0; i < s_word_iter; i++)
    {
        if (!isalpha(s_word[i]))
        {
            continue;
        }

        s_word_acc += w_score[toupper(s_word[i]) - 'A'];
    }
    
    if (f_word_acc > s_word_acc)
    {
        printf("Player 1 wins!\n");
    } else if (s_word_acc > f_word_acc)
    {
        printf("Player 2 wins!\n");
    } else
    {
        printf("Tie!\n");
    } 
    
    return 0;
}