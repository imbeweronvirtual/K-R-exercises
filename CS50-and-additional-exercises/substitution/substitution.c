/*
    THIS CODE WORKS ONLY WITH
    CS50 LIBRARY, WHICH CAN BE
    USED ON https://cs50.dev 
    WEBSITE
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define KEY_LENGTH 26

void encrypt_msg(string message, char key[]);

int main(int argc, char *argv[])
{
    char is_there[KEY_LENGTH];
    for (size_t i = 0; i < KEY_LENGTH; i++)
    {
        is_there[i] = 0;
    }

    if (argc != 2)
    {
        printf("Error is occured. The key must be inputed\n");
        return 1;
    }

    if (strlen(argv[1]) != KEY_LENGTH)
    {
        printf("Error is occured. The key must be 26 characters long\n");
        return 1;
    }

    for (size_t i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Error is occured. The key must be a alphabetic characters string\n");
            return 1;
        }

        argv[1][i] = toupper(argv[1][i]);

        if (is_there[argv[1][i] - 'A'] == 1)
        {
            printf("Error is occured. The key must contain each letter only once\n");
            return 1;
        }
        else
        {
            is_there[argv[1][i] - 'A']++;
        }
    }

    string str_to_encrpt = get_string("plaintext: ");
    encrypt_msg(str_to_encrpt, argv[1]);

    return 0;
}

void encrypt_msg(string message, char key[])
{
    printf("ciphertext: ");

    for (size_t i = 0; message[i] != '\0'; i++)
    {
        if (isalpha(message[i]))
        {
            if (isupper(message[i]))
            {
                printf("%c", key[message[i] - 'A']);
            }
            else
            {
                printf("%c", tolower(key[toupper(message[i]) - 'A']));
            }
        }
        else
        {
            printf("%c", message[i]);
        }
    }

    printf("\n");
}
