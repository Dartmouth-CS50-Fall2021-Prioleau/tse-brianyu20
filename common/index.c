/** 
 * index.c - index module 
 * 
 * more information on index.h
 * 
 * Brian Yu
 * 10/21/21
 * Lab 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../libcs50/webpage.h"
#include "../libcs50/file.h"

typedef struct index{
    hashtable_t* hashtable;
} index_t;

void index_item_delete(void* item);
void itemprint(void* arg, const char* key, void* item);
void counters_itemprint(void* arg, const int key, const int number);

/**************** functions ****************/

//making a new index. see index.h for more information
index_t* index_new(const int numslots){

    //allocate memory for a new index struct
    index_t* index = malloc(sizeof(index_t));

    //give it a hashtable
    index->hashtable = hashtable_new(numslots);

    return index;
}

//deleting index. see index.h for more information
void index_delete(index_t* index){
    if (index != NULL){
        hashtable_delete(index->hashtable, index_item_delete);
        free(index);
    }
    
}

//local helper function for index_delete
void index_item_delete(void* item){
    counters_delete(item);
}

//see index.h for more information.
counters_t* index_find(index_t* index, void* key){
    
    if (index != NULL && key != NULL){
        return hashtable_find(index->hashtable, key);
    }
    else{
        return NULL;
    }

}

//see index.h for more information
void index_insert(index_t* index, void* key, void* item){
    if (index != NULL && key != NULL){
        hashtable_insert(index->hashtable, key, item);
    }
}

//see index.h for more information
void index_save(char* filename, index_t* index){
    FILE* fp; 
    fp = fopen(filename, "w");
    hashtable_iterate(index->hashtable, fp, itemprint);
    fclose(fp);
}

//local function to help index_save
void itemprint(void* arg, const char* key, void* item){
    
    FILE* fp;
    fp = arg;
    //print the word first. '\n' is not included because more information has to come on that line.
    fprintf(fp, "%s ", key);
    
    //need to now iterate through the counters for that word
    counters_t* counters = item;
    counters_iterate(counters, fp, counters_itemprint);
    fprintf(fp, "\n");
}

//local function to help index_save by helping itemprint
void counters_itemprint(void* arg, const int key, const int number){
    
    FILE* fp;
    fp = arg;
    //printing in the right format now
    fprintf(fp, "%d %d ", key, number);
}

//more information on index.h
void index_load(char* filename, index_t* index){
    FILE* fp;
    fp = fopen(filename, "r");

    //initialize variables
    char* word;
    int ID;
    int number;
    //boolean to keep track of the number pairs in the index
    bool first = true;

    //loop through the words in file
    while ((word = freadwordp(fp)) != NULL){
        //save the scanned information in the variables
        
        while (fscanf(fp, "%d %d", &ID, &number) == 2){
            //use the variables to build the index  
            //different algorithm from index_build
            // if it's the first pair of numbers for that word
            if (first){
                counters_t* counters = counters_new();
                //set the counters as the ID and number 
                counters_set(counters, ID, number);
                index_insert(index, word, counters);
                first = false;
            }
            //if it's not the first pair of numbers for that word
            else{
                counters_set(index_find(index, word), ID, number);
            }
            
        }
        first = true;
        free(word);
    }
    fclose(fp);

}

#ifdef UNIT_TEST
int test_index() {
    index_t* index = index_new(200);
    EXPECT (index != NULL);

    index_insert(index, "keycheck", "itemcheck");
    EXPECT (index_find(index, "keycheck") == "itemcheck"));

    index_delete(index);
    EXPECT (index == NULL);

    END_TEST_CASE;
    return TEST_RESULT;
}



#endif // UNIT_TEST