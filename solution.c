#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define STRING_MAX_LENGTH 10000 // the length that can be readed in one iteration
#define TAB_LENGTH 4 // in some editors the length of tab is different, but normal value is 4 spaces in one tab

int main() {
    int chars_limit = 0; // how many chars does the user want to see in one string

    // FILE *fptr = fopen("input.txt", "r");

    {
        char c; // temporary variable to store getchar() value
        short res = 0; // to store return value from scanf()
        char last_char; // to store the \n symbol so the code can know where's the end of string
        while (1)
        {
            printf("Enter how many chars do you want to see in one string: ");
            res = scanf("%d%c", &chars_limit, &last_char);
            if (res == EOF)
            {
                return 1;
            }
            if (chars_limit > 0 && isspace(last_char))
            {
                break;
            }
            while ((c = getchar()) != '\n' && c != EOF); // cleaning buffer if scanf didn't take all of values
        }
    }

    char *str = malloc(sizeof(char) * STRING_MAX_LENGTH); // allocating memory for string array
    if (str == NULL)
    {
        return 1;
    }
    
    clock_t start_time = clock();

    while (fgets(str, STRING_MAX_LENGTH, stdin) != NULL) // save input from terminal in str array
    {
        const unsigned int str_length = strlen(str);
        unsigned int *index_array = NULL; // declare pointer in while scope so the program can allocate memory later
        bool *copy_or_replace_array = NULL; // declare pointer in while scope so the program can allocate memory later
        unsigned int size = (double)str_length / chars_limit; // potentially size for index_array and copy_or_replace_array, not precise
        
        if (str_length > chars_limit)
        {
            /*
            these two arrays(index & copy_or_replace) working together, the first one
            stores indexes where the program need to place \n, the second one stores
            true/false values where true is to chenge char on this index in str array
            and false is to add \n after this index in str array, example:
            index_array = [5]
            copy_or_replace_array = [1]

            str = ['h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd']

            str after formatting = ['h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd']
            */
            index_array = malloc(sizeof(unsigned int) * size);
            copy_or_replace_array = malloc(sizeof(bool) * size);
            
            if (index_array == NULL)
            {
                return 1;
            }
            if (copy_or_replace_array == NULL)
            {
                return 1;
            }
        } else // if string was smaller then chars_limit program can just print the original string
        {
            for (size_t i = 0; str[i] != '\0'; i++)
            {
                printf("%c", str[i]);
            }
            continue;
        }
        
        
        /*
        if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
        */
       
        unsigned long index_array_index = 0; // iterator
        unsigned int length = 0; // length of already checked chars
        bool is_succesful = false; // variable to spot other cycle if the first one worked succesfully
        index_array[0] = 0; // initializing only first element of index_array because if not it can lead to condition jump

        for (unsigned int i = 0; i < str_length; i++)
        {
            if (str[i] == '\t') 
            {
                length += TAB_LENGTH - (length % TAB_LENGTH); // tabs are not arways one or four spaces, so we need to always check how many spaces
                                                              // does the one print
            } else
            {
                length++;
            }
            
            if (length > chars_limit)
            {
                if (str[i] == '\n')
                {
                    is_succesful = true; // if the char is already \n there's no need to do something
                }
                
                if (index_array_index + 1 > size)
                {
                    /*
                    if index_array and copy_or_replace_array are full we reallocate the memory by multipliyng
                    the origin size by 2
                    */
                    size *= 2;
                    {
                        unsigned int *temp = realloc(index_array, sizeof(unsigned int) * size);
                        if (temp == NULL)
                        {
                            printf("UNSUCCS");
                            free(str);
                            free(index_array);
                            free(copy_or_replace_array);
                            return 1;
                        }
                        index_array = temp; // if succesful store new pointer in old one
                    }
                    {
                        bool *temp = realloc(copy_or_replace_array, sizeof(bool) * size);
                        if (temp == NULL)
                        {
                            printf("UNSUCCS");
                            free(str);
                            free(index_array);
                            free(copy_or_replace_array);
                            return 1;
                        }
                        copy_or_replace_array = temp; // if succesful store new pointer in old one
                    }
                    
                }
                
                
                bool is_edge = false; // varible to see if cycle is already on the edge and there's no possible characters behind left

                for (unsigned int j = i - 1; j > 0 && !is_succesful; j--)
                {
                    switch (index_array_index > 0)
                    {
                    case true:
                        if (index_array[index_array_index - 1] == j)
                        {
                            is_edge = true;
                        }
                        break;
                    
                    default:
                        if (index_array[index_array_index] == j)
                        {
                            is_edge = true;
                        }
                        break;
                    }


                    if (isspace(str[j]) && !is_succesful && !is_edge)
                    {
                        index_array[index_array_index] = j;
                        copy_or_replace_array[index_array_index] = 1;
                        i = j;
                        index_array_index++;
                        length = 0;
                        is_succesful = true;
                        break;
                    }
                }

                if (!is_succesful)
                {
                    index_array[index_array_index] = i - 2;
                    i -= 2;
                    copy_or_replace_array[index_array_index] = 0;
                    index_array_index++;
                    length = 0;
                }
                
                is_succesful = false;
            }
        }

        
        for (size_t i = 0; i <= index_array_index - 1; i++)
        {
            printf("amount: %ld position: %d and t/f: %d\n", index_array_index, index_array[i], copy_or_replace_array[i]); // DEBUG
        }
        
        {
            int index_array_index_max_possible = index_array_index - 1; // store the amount of stored indexes in array
            index_array_index = 0;

            for (size_t i = 0; i < str_length; i++)
            {
                if (index_array[index_array_index] == i) // checking if program needs to place \n on this index(or after this index)
                {
                    switch (copy_or_replace_array[index_array_index])
                    {
                    case true:
                        printf("\n"); // just place \n on this index (explanation on main:52)
                        break;
                    
                    case false:
                        printf("%c", str[i]);
                        printf("\n"); // place \n after this index (explanation on main:52)
                        break;
                    }
                    if (index_array_index + 1 <= index_array_index_max_possible) // if the value was already checked moving in index array futher
                    {
                        index_array_index++;
                    }
                    
                    continue;
                }
                printf("%c", str[i]);
                
            }
        }

        // free(index_array);
        index_array = NULL;

        free(copy_or_replace_array);
        copy_or_replace_array = NULL;
    }

    free(str);
    str = NULL;
    
    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("\nDone in %.3f seconds\n", elapsed_time);

    return 0;
}
