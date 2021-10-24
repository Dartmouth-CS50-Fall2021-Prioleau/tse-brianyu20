/** 
 * pagedir.c - pagedir module 
 * 
 * more information on pagedir.h
 * 
 * Brian Yu
 * 10/14/21
 * Lab 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pagedir.h"
#include "../libcs50/webpage.h"
#include "../libcs50/hashtable.h"

bool check_directory(char* pageDirectory){

    //allocate memory to create a filename to test if that opens and is writable
    FILE* fp = NULL;
    char* filename = malloc(strlen(pageDirectory)+10);
    
    sprintf(filename, "%s/.crawler", pageDirectory);
    
    //if it's null, free the memory and return false.
    if ((fp = fopen(filename, "w")) == NULL){
        free(filename);
        return false;
    }
    //if it's successfull, close the file, free the memory and return true
    else {
        fclose(fp);
        free(filename);
        return true;
    }

}

void write_directory(char* pageDirectory, webpage_t* page, int ID){
    //initializing file pointer and filename
    FILE* fp = NULL;
    char* filename = (char*) malloc(strlen(pageDirectory)+ sizeof(ID)+ 10);

    sprintf(filename, "%s/%d", pageDirectory, ID);
    
    //if it can't open it, log the error
    if ((fp = fopen(filename, "w")) == NULL){
        fprintf(stderr, "There was an error in writing the file\n");
        
    }
    //if not, write in the file according to format
    else{
        
        fprintf(fp, "%s\n", webpage_getURL(page));
        fprintf(fp, "%d\n", webpage_getDepth(page));
        fprintf(fp, "%s\n", webpage_getHTML(page));
        fclose(fp);
    }
    free(filename);

}

//see pagedir.h for more information
bool pagedir_validate(char* filename){
    FILE* fp = NULL;
    //char* file = (char*) malloc(strlen(filename)+ 10);
    //file = filename; 
    fp = fopen(filename, "r");

    if (fp != NULL){
        fclose(fp);
        //free(file);
        return true;
    }
    else{
        //free(file);
        fprintf(stderr, "couldn't read the file\n");
        return false;
    }
    //free(filename);
}