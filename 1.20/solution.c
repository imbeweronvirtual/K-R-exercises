#include <stdio.h>

#define TAB_LENGTH 8

int main()
{
    char c;
    unsigned int length = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            unsigned int temp = TAB_LENGTH - (length % TAB_LENGTH);
            if (temp == 0)
            {
                for (size_t i = 0; i < TAB_LENGTH; i++)
                {
                    putchar(' ');
                }
                
            } else 
            {
                for (size_t i = 0; i < temp; i++)
                {
                    putchar(' ');
                }
            }
            
            length = 0;

        } else if (c == '\n')
        {
            putchar(c);
            length = 0;
        } else
        {
            length++;
            putchar(c);
        }
        
        
    }
    
    return 0;
}
