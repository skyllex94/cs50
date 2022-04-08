// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 25;

// Hash table
node *table[N];
unsigned int hash_value;
unsigned int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (sizeof(word) != 0)
    {
        for (int i = 97; i < (97 + N); i++)
        {
            if (word[0] == i)
            {
                node *hashed_word = malloc(sizeof(node));
                table[i]->word = hashed_word;
            }
        }
    }

    // return a_number;
    return 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Read dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file != NULL)
    {
        // Initialize a string to populate the data with it can be further used
        char *dic_word = NULL;
        // Scan each word in the dictionary until the end of the file
        while (fscanf(file, "%c", dic_word) != EOF)
        {
            // Allocate memory dynamically for each word using the node struct
            node *current_word = malloc(sizeof(node));
            // Copy the content of the current word into memory
            strcpy(current_word->word, dic_word);
            // Hash the current dictionary word
            char first_letter = 97 + islower(dic_word[0]);
            for (int i = 0; i < N; i++)
            {
                if (strcmp(dic_word[0], first_letter) == 0)
                {
                    if (sizeof(table[i]->word) != 0)
                    {
                        current_word->next = table[i]->word;
                        table[i] = current_word;
                        table[i]->word = current_word->word;
                    }
                    table[i] = current_word;
                    table[i]->word = current_word->word;
                }
            }
            hash(dic_word);
            return true;
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count != 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload()
{
    // while (dictionary != NULL)
    // {
    //     dictionary->
    // }
    return false;
}
