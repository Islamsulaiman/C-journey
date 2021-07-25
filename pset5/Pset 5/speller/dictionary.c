// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"
#include <cs50.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];      //+1 is for the null character.
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;     //(26*26+1) to lock for the first two chars, prime number to work with hashing by division.
unsigned int counter = 0;       //counter for the no. of words.


// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO: send the word to hash() to get hash_value.
    unsigned int hash_value = hash(word);
    // TODO: make temp node to loop over the linked list in table[hash_value].
    node *temp = table[hash_value];
    // TODO: loop over the linked list searching for the word, return true if found.
    while (temp != NULL)
    {
        if (strcasecmp(word,temp->word) == 0)

            return true;

        temp = temp->next;
    }
    // TODO: free temp.
    free(temp);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)     //if the string inside a dectionarry, transform that string into number that will be equal to it every time.
{
    //h(word) = k % N  ,division methon , set m as 677 wich is (26*26+1)
    //take a word from load() function
    // TODO: calculate the key .
    unsigned int key = 0;     //to save the key

    for(int i = 0; word[i] != '\0'; i++)   //use != '\0' insted of strlen(word), because word is a pointer and that could generate problems.
    {
        key = tolower(word[i]);     //because dictionary is lowercase words we should convert input from text file to lowercase litter 1st
    }
    // TODO: calculate h
    unsigned int hash_value = key % N;
    // TODO: return the hash value to load()
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO: open the dictionary file in FILE pointer using fopen() and check for memory validity.
    FILE *ptr_in = fopen(dictionary,"r");
    if(ptr_in == NULL)
    {
        printf("\nError: memory failed to load word from dictionary\n");
        return false;
    }

    for (int i =0; i < N; i++)
    {
        table[i] = NULL;
    }

    char buffer [LENGTH + 1];       //size of the maximum letter length in the dictionary.

    // TODO: read string from file pointer using fscanf(file, "%s", &buffer).
    while (fscanf(ptr_in,"%s\n",buffer) != EOF)
    {
        // TODO: create new node, check if created, copy the word from buffer using strcpy(desnenation,source).
        node *temp = (node*) malloc (sizeof(node));
        if (temp == NULL)
        {
            printf("\nError: memory failed to load word from dictionary to buffer\n");
            free(buffer);
            fclose(ptr_in);
            return false;
        }
        strcpy(temp->word,buffer);

        // TODO: hash the word to get the place in the table using hash() function.
        unsigned int hash_value = hash(buffer);

        // TODO: insert the node into its place inside the table.
        if (table[hash_value] == NULL)        //if the header pointer in the table dosnt have linked list in it.
        {
            temp->next = NULL;
            table[hash_value] = temp;       //point to the 1st node at this header.
        }
        else        //if there at least one node after the header
        {
            temp->next = table[hash_value];           //make temp to point to 1st node.
            table[hash_value] = temp;                //make header point to temp to insert it at the first.
        }

        // TODO: use size() function to keep track of dictionary words.
        counter++;
    }
    fclose(ptr_in);
    // free(temp);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded

unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while(ptr != NULL)
        {
            node *DeletMe = ptr;
            ptr = ptr->next;
            free(DeletMe);
        }
        table[i] = NULL;
    }
    return true;
}