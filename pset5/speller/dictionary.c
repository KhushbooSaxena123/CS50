// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
//size of dictionary
unsigned int dic_size = 0;

// Number of buckets in hash table
const int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int head = hash(word);
    node *cursor;
    cursor = table[head];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor -> word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int value = 0;
    unsigned int c = strlen(word);

    for (int i = 0; i < c; i++)
    {
        value = value + 37 * tolower(word[i]);
    }
    value = value % N;
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char WORD[LENGTH + 1];
    // open dictionary
    FILE *dic = fopen(dictionary, "r");
    // check if it is not null
    if (dic == NULL)
    {
        return false;
    }
    // read string from file
    while (fscanf(dic, "%s", WORD) != EOF)
    {
        // create a new node
        node *n = malloc(sizeof(node));

        // check if it is not null
        if (n == NULL)
        {
            return false;
        }
        strcpy(n -> word, WORD);
        n -> next = NULL;

        //Hash the word
        int head = hash(WORD) ;
        // insert node into hash table
        if (table[head] == NULL)
        {
            table[head] = n;
        }
        else
        {
            n -> next = table[head];
            table[head] = n;
        }

        dic_size += 1;
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dic_size;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *temp;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        temp = table[i];
        while (cursor != NULL)
        {
            cursor = cursor -> next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
