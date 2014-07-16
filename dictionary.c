/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // starting position of where we are in the char
    int position = 0;
    int n = strlen(word);
    char lowerCase[LENGTH];
    
    // converts each upper case character to a lower case
    for (int i = 0; i < n; i++)
    {
        if (isalpha(word[i]) != 0)
        {
            if (isupper(word[i]) != 0)            
                lowerCase[i] = word[i] - 'A' + 'a';                
            
            else if (islower(word[i]) != 0)
                lowerCase[i] = word[i];
        }
        else
            lowerCase[i] = word[i];
    }
    
    // calling the function to find out if word is in the trie
    // passing in the pointer for the root part of the trie.
    if(TrieHarder(lowerCase, n, position, root) == true)
        return true;
                   
    return false;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = malloc(sizeof(trie));
    char word[LENGTH + 1]; 
    
    // counts the number of words in the dictionary
    counter = 0;
    
    if (root == NULL)
        return false;
   
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
        return false;   
    
    // goes through dictionary word by word and calling TrieAgain until fscanf gets to end of file
    while(fscanf(fp, "%s", word) != EOF)
    {
        counter++;
        
        if(TrieAgain(word, 0, root) == false)
            return false;
    }
    
    fclose(fp);
    
    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return counter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return TrieSomeMore(root);
}
/**
 * Recurssively calls itself to fill in a trie returns false if unable to allocate memory
 */
bool TrieAgain (char* word, int position, trie* root)
{
    char letter = word[position];
    int index;  // variable for the location in the trie to look for a child
    
    // finds the letter in position and subtracts the ascii value of a from it to
    // find an int for its child position, 26 for apostrophe

    if (isalpha(letter) != 0)
        index = letter - 'a';    
    
    else 
        index = 26;
          
    if (position + 1 == strlen(word) && root->children[index] != NULL)  
    {
        root -> children[index] -> isWord = true;
        return true;  
    }
    
    if (position + 1 == strlen(word) && root -> children[index] == NULL)
    {
        root->children[index] = malloc(sizeof(trie));
        root -> children[index]-> isWord = true;
        return true;
    }
        
        
    // creates a new trie, allocates the memorry and recurssively calls itself
    else if (root -> children[index] == NULL)
    {
        root -> children[index] = malloc(sizeof(trie));
        return TrieAgain (word, position + 1, root -> children[index]);
    }
    
    
    // since the child of the trie exists we follow that path and execute again     
    else
        return TrieAgain (word, position + 1, root -> children[index]);   
}        
   
/**
 *  Checks the word against each child recurssively where position keeps track  
 *  of where we are in the word.  Returns true if the word is there
 */
bool TrieHarder (char* word, int length, int position, trie* root)
{   
    //converts current char to a number representing a postion in the trie
    int num;
    
    if (isalpha(word[position]) != 0)
        num = word[position] - 'a';        
    else
        num = 26;
    
    if (position == length && root -> isWord == true)
        return true;
    
    if (position == length && root -> isWord == false)
        return false;
          
    else 
        if (root->children[num] == NULL)
            return false;
        else    
            return TrieHarder(word, length, position + 1, root-> children[num]);
     
    return false;    
}

/*
 *  Frees memory of the trie starting with the lowest child starting with a going to z
 */
bool TrieSomeMore (trie* root)
{
    for (int i = 0; i < 27; i++)
    {
        if (root -> children[i] != NULL)
            TrieSomeMore(root->children[i]);
    }
    
    free(root);
    
    return true;
}    
