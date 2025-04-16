#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 1000
#define MAX_STRING_AMOUNT_LENGTH 500


int main()
{
    char str[MAX_STRING_AMOUNT_LENGTH][MAX_STRING_LENGTH];

    long index = 0;

    while(fgets(str[index], MAX_STRING_LENGTH, stdin) != NULL)
    {
        index++;
        if (index >= MAX_STRING_AMOUNT_LENGTH)
        {
            break;
        }
    } // test if this works

    /*
    multiple stirngs can be hard
    */

   bool in_comments_single = false;
   bool in_comments_multiple = false;
   
   for (size_t i = 0; i < index; i++)
   {
        bool in_qoutes = false;
        bool in_escape = false;
        unsigned int in_escape_scope_end = 0;
        for (size_t j = 0; j < MAX_STRING_LENGTH && str[i][j] != '\0'; j++)
        {
            char current_char = str[i][j];
            char next_char = str[i][j + 1];

            if (in_escape_scope_end == j)
            {
                in_escape = false;
            }
            

            if (!in_qoutes && !in_escape && current_char == '/')
            {
                if (next_char == '/')
                {
                    while (str[i][j] != '\n')
                    {
                        j++;
                    }
                }
                else if (next_char == '*')
                {
                    in_comments_multiple = true;
                    j += 2;
                    continue;
                }
            } else if (!in_qoutes && !in_escape && current_char == '*')
            {
                if (next_char == '/')
                {
                    in_comments_multiple = false;
                    j += 2;
                }
            } else if (current_char == '"' || current_char == '\'' && !in_escape)
            {
                switch (in_qoutes)
                {
                case true:
                    in_qoutes = false;
                    break;
                
                default:
                    in_qoutes = true;
                    break;
                }
            } else if (current_char == '\\' && !in_qoutes)
            {
                in_escape_scope_end = j + 2;
                in_escape = true;
            }
            
            if (!in_comments_multiple)
            {
                printf("%c", str[i][j]);
            }
            
        }
        
    }
    
    

    

    return 0;
}