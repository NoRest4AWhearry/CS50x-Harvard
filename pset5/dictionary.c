/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

#define HASHTABLE 26
#define LENGTH 45

// create struct for linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

// create hashtable as node
node* hashtable[HASHTABLE];

// create hash function
int hashit(const char* key)
{
    int hash = toupper(key[0]) - 'A';
    return hash % HASHTABLE;
}

// initialize dictionary size;
int dictionarySize = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    
    // convert letters of word to lower case
    char lowerWord[LENGTH +1];
    for (int i = 0; i <= strlen(word); i++)
    {
       lowerWord[i] = tolower(word[i]);
    }
    
    // hash word to find which bucket it would be in;
    int index = hashit(lowerWord);
    
    // create new node and set it to the head of the bucket;
    node* checker = hashtable[index];
    
    // loop until checker equal to NULL
    while (checker != NULL)
    {
        // compare strings in checker-word to word to find mach
        if (strcmp(checker->word, lowerWord) == 0)
        {
            return true;
        }
        // if not a match, point checker to next word;
        checker = checker->next;
    }
    // if word not found
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    // initialize word
    char word[LENGTH + 1];
    
    // open dictionary file
    FILE* dict = fopen(dictionary, "r");
    
    // check if dictionary exists
    if (dict == NULL)
        return false;
        
    // interate over dictionary
    while (fscanf(dict, "%s", word) != EOF)
    {
        // allocate memory to new node
        node* newNode = malloc(sizeof(node));
        
        // assign newnode word to word in file
        strcpy(newNode->word, word);
        
        // create index value
        int index = hashit(newNode->word);
        
        // insert words
        if (hashtable[index] == NULL)
        {
            hashtable[index] = newNode;
            newNode->next = NULL;
        }
        // if not null, append words;
        else
        {
            newNode->next = hashtable[index];
            hashtable[index] = newNode;
        }
        dictionarySize++;
    }
    //close dictionary file
    fclose(dict);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    // determine size
    if (dictionarySize > 0)
        return dictionarySize;
    else
        return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    for (int i = 0; i <= HASHTABLE; i++)
    {
        node *cursor = hashtable[i];
        while (hashtable[i] != NULL)
        {
            
            hashtable[i] = cursor->next;
            free(cursor);
            return true;
        }
    }
    return true;
}
