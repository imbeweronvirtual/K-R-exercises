// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 20000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lc_word[LENGTH + 1];
    for (int i = 0;; i++)
    {
        if (word[i] == '\0')
        {
            lc_word[i] = '\0';
            break;
        }
        lc_word[i] = tolower(word[i]);
    }
    unsigned int word_hash = hash(lc_word);
    node *tmp = table[word_hash];
    while (tmp != NULL)
    {
        if (strcmp(tmp->word, lc_word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}

// Hashes word to a number with hint DJB2 algorithm from CS50 Duck
unsigned int hash(const char *word)
{
    unsigned long long hash = 5381;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = hash * 33 + word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *ptr = fopen(dictionary, "r");
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    if (ptr == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(ptr, "%s", word) != EOF)
    {
        node *current = malloc(sizeof(node));
        strcpy(current->word, word);
        unsigned int word_hash = hash(word);
        current->next = table[word_hash];
        table[word_hash] = current;
    }

    fclose(ptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;
    node *current;
    for (size_t i = 0; i < N; i++)
    {
        current = table[i];

        while (current != NULL)
        {
            count++;
            current = current->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *current;
    node *tmp;
    for (size_t i = 0; i < N; i++)
    {
        current = table[i];

        while (current != NULL)
        {
            tmp = current->next;
            free(current);
            current = tmp;
        }
    }

    return true;
}
