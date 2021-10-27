/** 
 * Lab 5; Indexer
 * Brian Yu
 * 10/20/21
 * Usage: ./indexer pageDirectory indexFilename
 * Purpose: Builds a datastructure mapping words to a document and how many times that word occurs in that document. 
 * More details in DESIGN.md and IMPLEMENTATION.md
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/file.h"
#include "../common/pagedir.h"
#include "../common/index.h"
#include "../common/word.h"
#include "../libcs50/webpage.h"

//function prototype
void index_build(char* directory, index_t* index);

int main (int argc, char *argv[]){

    //parsing and validating arguments. 
    //validating the number of arguments
    if (argc != 3){
        fprintf(stderr, "See correct usage again.\n");
        return 1; 
    }

    //checking that they aren't null
    for (int i=0; i < 3; i++){
        if (argv[i] == NULL){
            fprintf(stderr, "Not all arguments are valid.\n");
            return 1;
        }
    }

    //initializing the arguments
    //directory
    char* directory = (char*)malloc(strlen(argv[1])+10);
    strcpy(directory, argv[1]);
    //filename
    char* filename = (char*)malloc(strlen(argv[2]+10));
    strcpy(filename, argv[2]);

    //initializing data structure
    index_t* new_index = index_new(500);


    //checking that pageDirectory exists and is produced by crawler
    if (check_directory(directory)){ 
        if (pagedir_validate(filename)){
            index_build(directory, new_index);
            index_save(filename, new_index);
        }
        //proceed with building the datastructure and then saving that to the filename 
        else{
            fprintf(stderr, "directory or file is wrong\n");
        }
    }
    else{
        fprintf(stderr, "directory or file is wrong\n");
    }

    //free all memory allocated
    index_delete(new_index);
    free(directory);
    free(filename);
    return 0;
}

void index_build(char* directory, index_t* index){
    //Initial doc ID
    int ID = 1;
    char* directory_ID = malloc((strlen(directory)+20 *(sizeof(char*)))); //find a better way to allocate memory specific for the ID
    //concatenate directory and ID
    sprintf(directory_ID, "%s/%d", directory, ID);

    //progress check
    printf("current file name is %s\n", directory_ID);

    //first while loop is to loop through the files in the directory 
    while(pagedir_validate(directory_ID)){

        FILE* fp;
        fp = fopen(directory_ID, "r");

        //get to the third line
        char* url = freadlinep(fp);
        
        //need an intermediary variable depthp to free it without interfereing with int
        char* depthp = freadlinep(fp);
        int depth = (atoi)(depthp);
        free(depthp);

        //the rest of the file is all html, so use freadfilep
        char* html = freadfilep(fp);
        int pos = 0;

        //save the information to a webpage struct
        webpage_t* webpage = webpage_new(url, depth , html);
        //initializing
        char* word; 
        
        //this nested loop is to loop through the words in the file 
        while((word = webpage_getNextWord(webpage, &pos)) != NULL){
            if (strlen(word)>3){
                
                normalize_word(word);

                //if it's the first time that the word is seen
                if (index_find(index, word) == NULL){
                    //add a new counters for that word. 
                    counters_t* new_counters = counters_new();
                    counters_add(new_counters, ID);
                    //and add a new entry in the index
                    index_insert(index, word, new_counters);

                }
                //if it's not the first time, 
                else{
                    //retrieve the pointer to the counters, and use the doc ID to increment the count
                    counters_add((index_find(index,word)), ID);
                }
            }
            free(word);
            pos++;
        }
        ID++;

        webpage_delete(webpage);
        fclose(fp);

        sprintf(directory_ID, "%s/%d", directory, ID);
        printf("%s is the file right now\n", directory_ID);

    }
    free(directory_ID);
    
}
