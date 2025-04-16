#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define STRING_MAX_LENGTH 10000 // the length that can be readed in one iteration
#define TAB_LENGTH 4 // in some editors the length of tab is different, but normal value is 4 spaces in one tab

int limit_input();
void formatted_string_output(const char *original_array, unsigned int *array_of_indexes, bool *array_tf, const int amount);
void find_break(const char *original_array, unsigned int *array_of_indexes, bool *array_tf, unsigned long *amount, const int limit, int *i);

int main() {
    const int chars_limit = limit_input(); // how many chars does the user want to see in one string

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
            formatted_string_output(str, NULL, NULL, 0);
            continue;
        }
        
        
        /*
        if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
        */
       
        unsigned long index_array_iterator = 0; // iterator
        unsigned int length = 0; // length of already checked chars
        bool is_succesful = false; // variable to spot other cycle if the first one worked succesfully

        for (unsigned int i = 0; i < str_length; i++)
        {
            if (str[i] == '\t') 
            {
                length += TAB_LENGTH - (length % TAB_LENGTH); // tabs are not always one or four spaces, so we need to always check how many spaces
                                                              // does the one print
            } else
            {
                length++;
            }
            
            if (length > chars_limit)
            {
                if (index_array_iterator + 1 > size)
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
                            // free(index_array);
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
                            // free(copy_or_replace_array);
                            return 1;
                        }
                        copy_or_replace_array = temp; // if succesful store new pointer in old one
                    }
                    
                }
                
                if (str[i] != '\n')
                {
                    find_break(str, index_array, copy_or_replace_array, &index_array_iterator, chars_limit, &i);
                    length = 0;
                }
            }
        }

        /*
        for (size_t i = 0; i <= index_array_iterator - 1; i++)
        {
            printf("amount: %ld position: %d and t/f: %d\n", index_array_iterator, index_array[i], copy_or_replace_array[i]); // DEBUG
        }
        */

        formatted_string_output(str, index_array, copy_or_replace_array, index_array_iterator);

        free(index_array);
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

int limit_input()
{
    char c; // temporary variable to store getchar() value
    short res = 0; // to store return value from scanf()
    char last_char; // to store the \n symbol so the code can know where's the end of string
    int result = 0;
    while (1)
    {
        printf("Enter how many chars do you want to see in one string: ");
        res = scanf("%d%c", &result, &last_char);
        if (res == EOF)
        {
            return 1;
        }
        if (result > 0 && isspace(last_char))
        {
            break;
        }
        while ((c = getchar()) != '\n' && c != EOF); // cleaning buffer if scanf didn't take all of values
    }
    return result;
}

void formatted_string_output(const char *original_array, unsigned int *array_of_indexes, bool *array_tf, const int amount)
{
    unsigned int array_i = 0;
    const unsigned int string_length = strlen(original_array);


    if (amount < 1)
    {
        for (size_t i = 0; i < string_length; i++)
        {
            printf("%c", original_array[i]);
        }
        return;
    }
    

    for (size_t i = 0; i < string_length; i++)
    {
        if (array_of_indexes[array_i] == i) // checking if program needs to place \n on this index(or after this index)
        {
            switch (array_tf[array_i])
            {
            case true:
                printf("\n"); // just place \n on this index (explanation on main:52)
                break;
            
            case false:
                printf("%c", original_array[i]);
                printf("\n"); // place \n after this index (explanation on main:52)
                break;
            }
            
            if (array_i + 1 <= amount - 1) // if the value was already checked moving in index array futher
            {
                array_i++;
            }
            
            continue;
        }
        printf("%c", original_array[i]);
    }
}

void find_break(const char *original_array, unsigned int *array_of_indexes, bool *array_tf, unsigned long *amount, const int limit, int *i)
{
    bool is_succesful = false;

    for (unsigned int j = *i; j > 0 && !is_succesful && j > *i - limit; j--)
    {
        // if (*amount > 0)
        // {
        //     if (array_of_indexes[*amount - 1] == j)
        //     {
        //         is_edge = true;
        //     }
        // }

        if (isspace(original_array[j]) && !is_succesful)
        {
            array_of_indexes[*amount] = j;
            array_tf[*amount] = 1;
            *i = j;
            *amount += 1;
            is_succesful = true;
            break;
        }
    }

    if (!is_succesful)
    {
        array_of_indexes[*amount] = *i - 1;
        *i -= 1;
        array_tf[*amount] = 0;
        *amount += 1;
    }
}
