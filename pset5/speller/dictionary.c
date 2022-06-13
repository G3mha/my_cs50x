// Implements a dictionary's functionality
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
unsigned int counter =  0; // creating the counter for the loading function
const unsigned int N = 26; // setting the number of buckets in the hash table with the number of letters on ASCII

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_number = hash(word); // getting the hash number
    node *cursor = table[hash_number]; // getting the node of this hash table
    while (cursor != NULL) // while the hashing process is still sucessful
    {
        if (strcasecmp(cursor->word, word) == 0) // comparing the string word with its allocation on memory, and dictionary
        {
            return true; // the word is in the dictionary, correctly allocated
        }
        cursor = cursor->next; // re-alocating
    }
    return false;  // the word is not in the dictionary
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash += tolower(word[i]);
    }
    return (hash % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r"); // opening the file to get the dictionary out of it
    // If there's no dictionary filem loaded, ends this function
    if (file == NULL)
    {
        return false;
    }
    for (int i = 0; i < N; i++)\
    {
        table[i] = NULL;
    }
    char word[LENGTH + 1];  // initializing a string to be used on the while
    while (fscanf(file, "%s\n", word) != EOF)
    {
        node *temporary = malloc(sizeof(node));
        strcpy(temporary->word, word); // copies into node after malloc suceeded
        int hash_number = hash(word);  // getting the hash out of the string
        if (table[hash_number] == NULL) // if there's a error on the memory allocation, end this function
        {
            temporary->next = NULL;
            table[hash_number] = temporary;
        }
        else  // if there's a hash number, allocate the table on next
        {
            temporary->next = table[hash_number];
            table[hash_number] = temporary; // re-feeding the the table with the content stored on temporary
        }
        counter += 1; // increasing the counter
    }
    fclose(file); // close the file and warn the algorithm that the loading suceeded
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter; // finally we are using the counter for something LOL (just kinding, I draw its necessity from the begining)
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) // runs i until its value is one less than the number of buckets in hash table
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp); // exiting the node that was used by the table hash
        }
        table[i] = NULL;
    }
    return true; // everything worked out just fine
}
