// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_value = hash(word);
    if(table[hash_value] == NULL)
    {
        return false;
    }
    else
    {
        for(node *n = table[hash_value]; n != NULL; n = n->next)
        {
            if(strcasecmp(n->word, word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash_value = toupper(word[0]) - 'A';
    if(hash_value > N)
    {
        hash_value %=  N;
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");
    if(source == NULL)
    {
        printf("Loading failed\n");
        return false;
    }
    for(int i = 0; i < N; i++)
    {
        table[i]=NULL;
    }
    char buffer[LENGTH + 1];
    while(fscanf(source, "%s", buffer) != EOF)
    {
        unsigned int hash_value = hash(buffer);
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            printf("Loading failed\n");
            return false;
        }
        strcpy(n->word, buffer);
        if(table[hash_value] == NULL)
        {
            table[hash_value] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[hash_value];
            table[hash_value] = n;
        }
        count++;
    }
    // TODO
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *ptr;
        node *n = table[i];
        while(n != NULL)
        {
            ptr = n->next;
            free(n);
            n = ptr;
        }
    }
    return true;
}
