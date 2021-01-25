// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 512;

// Hash table
node *table[N];

//counter variable to count number of words in dictionary loaded in hash table
int counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //ensure word is converted to lower case to produce the correct hash key
    char lowercase[LENGTH + 1];


    for (int i = 0; i < (strlen(word) + 1); i++)
    {

        lowercase[i] = tolower(word[i]);

    }


    int index = hash(lowercase);

    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number - using djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c;    /* hash * 33 + c */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary file using fopen
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    //read strings from file using fscanf
    char word[LENGTH + 1];

    while (fscanf(inptr, "%s", word) != EOF)
    {


        //hash word using hash function
        int index = hash(word);

        //create new node using malloc
        node *n = malloc(sizeof(node));

        //copy word into new node
        strcpy(n->word, word);
        n->next = NULL;

        //insert into the hash table
        if (n != NULL)
        {

            n->next = table[index];
            table[index] = n;
            counter++;

        }
        else
        {
            return false;
        }
    }

    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp;

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

    }
    return true;
}
