#include <stdio.h>
#include <stdlib.h>

#define TAB 4

int main()
{
    char str[1000];
    char no_spaces_str[1000];
    while ((fgets(str, 1000, stdin)) != NULL)
    {
        unsigned int length = 0;
        unsigned short in_space_area = 0;
        unsigned int spaces_count = 0;
        size_t i;
        size_t i_nss;
        i_nss = 0;
        for (i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == ' ')
            {
                switch (in_space_area)
                {
                case 1:
                    spaces_count++;
                    break;
                default:
                    in_space_area = 1;
                    spaces_count++;
                    break;
                }
            } else if (in_space_area == 1)
            {
                unsigned short tab_length;
                tab_length = TAB - (length % TAB);
                if (tab_length == 0)
                {
                    tab_length = TAB;
                }
                
                while (spaces_count >= tab_length)
                {
                    spaces_count -= tab_length;
                    no_spaces_str[i_nss] = '\t';
                    i_nss++;
                    length += tab_length;
                    tab_length = TAB;
                }

                while (spaces_count != 0)
                {
                    spaces_count--;
                    no_spaces_str[i_nss] = ' ';
                    i_nss++;
                    length++;
                }
                in_space_area = 0;
                no_spaces_str[i_nss] = str[i];
                i_nss++;
                length++;  
            } else
            {
                no_spaces_str[i_nss] = str[i];
                i_nss++;
                length++;
            }
        }
        no_spaces_str[i_nss] = '\0';

        for (size_t i = 0; no_spaces_str[i] != '\0'; i++)
        {
            printf("%c", no_spaces_str[i]);
        }
    }
    
    return 0;
}
