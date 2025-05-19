#include <stdio.h>

#define lim 1000

int main()
{
    char c;
    for (size_t i = 0; i < lim-1; i++)
    {
        if ((c = getchar) == EOF)
        {
            break;
        }
        if (c == '\n')
        {
            break;
        }  
    }
    
    return 0;
}