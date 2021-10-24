/** 
 * word.h - header file for word module to be used in indexer
 * used to normalize the words; to make all letters in a word into lower case
 * 
 * Brian Yu, 10/21/2021, CS50 lab 5
 */

#include <stdio.h>
#include <ctype.h>

/**************** functions ****************/

/**************** normalize_word ****************/
/**
 * loops through all letters in a word
 * calls ctype function 'tolower' on each word
 * returns the word that has turned into all lower cases
 * 
 * on error, returns null. 
 */
char* normalize_word(char* word);
