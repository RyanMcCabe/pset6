/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// a trie structure
typedef struct trie
{
    bool isWord;
    struct trie* children[27];
}
trie;

// initial root structure of the trie
trie* root;

// counts how many, used in load and recieved in size
int counter;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Recurssively calls itself to fill in a trie returns false if unable to allocate to memory
 */
bool TrieAgain (char* word, int position, trie* root);

/**
 *  Checks the word against each child in the Trie structure looking for the word.  Returns true if the word is there
 */
bool TrieHarder (char* word, int length, int position, trie* root);

/*
 *  Frees memory of the trie starting with the lowest child starting with a going to z
 */ 
bool TrieSomeMore (trie* root);

#endif // DICTIONARY_H
