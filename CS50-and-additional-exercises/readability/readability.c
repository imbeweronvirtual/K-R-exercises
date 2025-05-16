#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main()
{
    char text[10000];
    unsigned int total_letters;
    unsigned int num_sentences;
    unsigned int num_words = 1;
    unsigned int text_iterator = 0;

    printf("Text: ");
    fgets(text, 10000, stdin);

    for (size_t i = 0; i < 10000 && text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            num_sentences++;
        }
        if (text[i] == ' ')
        {
            num_words++;
        }
        if (isalpha(text[i]))
        {
            total_letters++;
        }
    }
    
    float avg_letters = (float)total_letters / num_words * 100;
    float avg_sentences = (float)num_sentences / num_words * 100;
    int grade_index = round((0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8);

    if (grade_index >= 1 && grade_index <= 16)
    {
        printf("Grade %d\n", grade_index);
    }
    else if (grade_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
    
    return 0;
}