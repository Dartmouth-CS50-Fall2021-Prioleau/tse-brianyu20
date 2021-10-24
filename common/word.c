 /** 
 * word.c - word module 
 * 
 * more information on index.h
 * 
 * Brian Yu
 * 10/21/21
 * Lab 5
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

//see word.h for more information 
char* normalize_word(char* word){
    if (word != NULL){
        for (int i=0; i < strlen(word); i++){
        word[i] = tolower(word[i]);
        }
        return word;
    }
    else{
        return NULL;
    }
}