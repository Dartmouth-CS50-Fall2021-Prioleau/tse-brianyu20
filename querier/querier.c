/** 
 * Lab 6; Querier
 * Brian Yu
 * 10/29/21
 * Usage: ./querier pageDirectory indexFilename
 * Purpose: Reads a sequence of words provided by the user, finds all the documents that have matches, and then prints the documents in decreasing rank order. 
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
#include "../libcs50/counters.h"



/////function prototypes/////
char** words(char* query, int* number_of_elements);
bool check_words(char** words, int length);
bool is_and (char* word);
bool is_or (char* word);
bool is_and_or (char* word);
counters_t* intersection (counters_t* first, counters_t* second);
void intersection_helper (void *arg, const int key, const int count);
counters_t* Union (counters_t* first, counters_t* second); //capitalized for now
void union_helper (void*arg, const int key, const int count);
counters_t* running_sum(char** words, index_t* index, int number_of_elements);
int prompter(index_t* index, int* number_of_elements, char* directory);
void clean_query (char** query, int number);


//helper struct to hold two counters
typedef struct counters_helper {
    counters_t* counters1, *counters2;
} counters_helper_t;

//helper struct to hold docs and scores
typedef struct doc_score{
    int ID, score;
}doc_score_t;

typedef struct doc_array {
    doc_score_t** array;
    int size;
} doc_array_t;

counters_helper_t* counters_helper_new(void);
void doc_score_count_help(void* arg, const int key, const int count);
void doc_score_helper(void* arg, const int key, const int count);
doc_array_t* sorted_scores(doc_array_t* all_scores, int struct_number);
void struct_print(doc_array_t* all_scores, int struct_number, char* directory);


int main (int argc, char *argv[]){

    //validating the commandline is mostly taken from my indexer.c
    //checking right number of arguments
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
    char* indexFile = (char*)malloc(strlen(argv[2]+10));
    strcpy(indexFile, argv[2]);

    //keep validating
    //directory2 is just to make a new string for pageDirectory/.crawler
    //reason for the above is documented in pagedir.h
    char* checkCrawler = (char*)malloc(strlen(directory)+10);
    strcpy(checkCrawler, directory);
    strcat(checkCrawler, "/.crawler");
    printf("%s\n", checkCrawler);
    if (!pagedir_validate(checkCrawler)){
        fprintf(stderr, "Directory is not produced by crawler.c\n");
        return 1;
    }
    free(checkCrawler);

    //validate indexFilename
    if(!pagedir_validate(indexFile)){
        fprintf(stderr, "Invalid indexFilename.\n");
        return 1;
    }

    FILE* fp = fopen(indexFile, "r");
    int num_slots = lines_in_file(fp);
    index_t* index = index_new(num_slots);
    index_load(indexFile, index);
    fclose(fp);

    //call the function that will prompt the user
    int* number_of_elements = malloc(sizeof(int*)); 
    *number_of_elements = 0;
    if ( prompter(index, number_of_elements, directory) == 0){
        free(number_of_elements);
        free(directory);
        free(indexFile);
        index_delete(index);
        return 0;
    }
}

//will return an array pointing to the start of each words in the user input 
//checks that the words are composed of letters, and normalizes it
char** words(char* query, int* number_of_elements){
    char** words_pointers = malloc(strlen(query)+1);
    //char* rest;

    //to iterate line
    int i = 0;
    //to iterate words
    int j = 0;
    
    normalize_word(query);

    int length = strlen(query);

    while (i < length-1){
        //increment if the space is blank
        while (isspace(*query)){
            query++;
            i++;
        }
        //when it exits the above loop, check if it's a letter            
        //allocate new memory
        
        char* word = malloc(strlen(query)*sizeof(char)+1);
        strcpy(word, query);
        words_pointers[j] = word;
        j++; //only time we increment the number of elements is when a word is added
        //printf("%d\n", j);
        (*number_of_elements)++;

        int k = 0; //to keep track of how many letters it slides

        //loop until another white space is found. 
        while(isalpha(*query) != 0){
            query++;
            i++;
            k++;
        }
        //add a null character so that words knows that the word ended
        word[k] = '\0';
        query++;
        i++;
        
    }
    // printf("number of elements: %d\n", *number_of_elements);
    // printf("first word is %s\n", words_pointers[0]);
    // printf("second word is %s\n", words_pointers[1]);
    // printf("third word is %s\n", words_pointers[2]);

    return words_pointers; 
}

//function to check that the word array is in the right format
//checks that the 'and's and 'or's are used correctly. 
bool check_words(char** words, int length){
    //validate the word structure
    //first checking that it doesn't start with an and or or
    if (is_and(words[0]) || is_or(words[0])){
        fprintf(stdout, "input starts with a conjunction.\n");
        return false;
    }
    //then checking that two conjunctions are not used in a row
    int i = 0; 
    
    while (i < (length-1)){
        if (is_and(words[i]) || is_or(words[i])){
                if (is_and(words[i+1]) || is_or(words[i+1])){
                fprintf(stdout, "conjunctions were used twice in a row.\n");
                return false;
                }            
        }
        i++;
    }

    //finally checking that it doens't end with a conjunction
    if (is_and(words[(length-1)])){
        fprintf(stdout, "and was used at the end of the sentence.\n");
        return false;
    }

    if (is_or(words[(length-1)])){
        fprintf(stdout, "or was used at the end of the sentence.\n");
        return false;
    }

    return true; 

}

//simple function to check if a word is 'and'
bool is_and (char* word){
    if (word == NULL){
        return false;
    }
    
    if ((strcmp(word, "and")) == 0){
        return true;
    }
    
    return false;
    
}

//simple function to check if a word is 'or'
bool is_or (char* word){
    if (word == NULL){
        return false;
    }
  
    if ((strcmp(word, "or")) == 0){
        return true;
    }

    return false;
    
}

//checks if it's 'and' or 'or
bool is_and_or (char* word){
    if (is_or(word) || is_and(word)){
        return true;
    }

    return false;

}

counters_helper_t* counters_helper_new(void){
    counters_helper_t* new = malloc(sizeof(counters_helper_t*));
    if (new != NULL) {
        new->counters1 = counters_new();
        new->counters2 = counters_new();
        return new;
    }
    return NULL;
}

//function to be called when two words are joined by 'and'. 
//merges the two words and takes the smaller count for documents that they both appear in
counters_t* intersection (counters_t* first, counters_t* second){
    //make a new counters to save the intersection
    counters_t* result = counters_new(); //have to free this some time 
    
    counters_t* help[2] = {result, second};
    
    //using the helper function to iterate
    counters_iterate(first, &help, intersection_helper);

    return help[0];
}

//iterator helper function for intersection 
void intersection_helper (void *arg, const int key, const int count){
    //first naming variables for the counters_help struct because it's not separated in a module
    counters_t** help = arg;
    //this is the resulting counters
    counters_t* result = help[0];
    //this is the counters that's being compared
    counters_t* compare = help[1];

    //if the one being compared is actually seen in a doc that the first word appears in,
    if (counters_get(compare, key) > 0){
        //if the count for the word being compared in that doc is bigger than the first's count in that doc
        if (counters_get(compare, key) > count){
            // add the first word's count to the resulting counters
            counters_set(result, key, count);
        }
        //if the first word's count is bigger, or in fact equal (doesn't matter if it's equal. same count), 
        //add the compared word's count with that doc ID
        else{
            counters_set(result, key, (counters_get(compare, key)));
        }
    }
    
}

//function to be called when two words are joined by 'or'. 
counters_t* Union (counters_t* first, counters_t* second){
    //make a new counters to save the union
    counters_t* result = counters_new();

    //using the helper function
    //need to iterate twice because either word found in a doc (alone) also needs to be added
    counters_iterate(first, result, union_helper);
    counters_iterate(second, result, union_helper); 
    return result;
}

//helper function for Union
void union_helper (void* arg, const int key, const int count){
    //naming the variables
    counters_t* result = arg;

    //if it's not already in the resulting counters, add it. 
    if (counters_get(result, key) == 0){
        counters_set(result, key, count);
    }
    //else; if it's already there, add to the count. 
    else{
        counters_set(result, key, (counters_get(result, key)+count));
    }
}


counters_t* running_sum(char** words, index_t* index, int number_of_elements){
    
    counters_t* union_score = counters_new();
    int i = 0; //move with union
    int k = 1; //move iwth intersect

    //first word will always be a non-and-or so initialize.
    counters_t* intersected = index_find(index, words[0]);
    // printf("first word intersect state:");
    // counters_print(intersected, stdout);
    // printf("\n");
    //if there is an 'or' this will turn false
    bool only_unions = true;

    //for (i; i < number_of_elements-1 && k < number_of_elements;){
    while (i < number_of_elements-1 && k < number_of_elements){
        //handling words in a row
        printf("word handled is %s\n", words[k]);
        if (!is_and_or(words[k])){
            //printf("word is not and or or so it's intersected. intersect is:");
            intersected = intersection(intersected, index_find(index, words[k]));
            //counters_print(intersected, stdout);
            //printf("\n");
            k++; //increment
        }
        //if it's not a word, it could be and or or
        else{
            //if it is an or, call Union
            if (is_or(words[k])){
                //printf("word is or, so union state is:");
                union_score = Union(intersected, union_score);
                //counters_print(union_score, stdout);
                //printf("\n");
                only_unions = false;
                i = k;
                k++;
            }
            //if it is an and, just skip
            else{
                //printf("word is and so skip\n");
                k++;
            }
        }
    }
    

    if (only_unions){
        //printf("returned intersect score is:");
        // counters_print(intersected, stdout);
        // printf("\n");
        return intersected;
    }
    else{
        // printf("returned union score is:");
        // counters_print(union_score, stdout);
        // printf("\n");
        return union_score;
        
    }
}

doc_array_t* new_doc_array (int struct_number) {
    doc_array_t* new = malloc(struct_number*sizeof(doc_score_t*));
    if (new != NULL) {
        for (int i = 0; i < struct_number; i++) {
            new->array[i] = malloc(sizeof(doc_score_t));
        }
        return new;
    }
    return NULL;
}

int prompter(index_t* index, int* number_of_elements, char* directory){

    fprintf(stdout, "Query?");

    FILE* fp2 = stdin;
    counters_t* scores;

    char* query; 
    
    char** arranged_words;

    while (!feof(fp2)){
        query = freadlinep(fp2);
        
        arranged_words = words(query, number_of_elements);


        if (check_words(arranged_words, *number_of_elements)){
            clean_query(arranged_words, *number_of_elements);

            scores = running_sum(arranged_words, index, *number_of_elements);

            int struct_number = 0;
            
            counters_iterate(scores, &struct_number, doc_score_count_help);

            //printf("%d items in scores\n", struct_number);

            if (struct_number == 0){
                fprintf(stdout, "No Documents Match\n");
            }
            else{
                doc_array_t* all_scores = new_doc_array(struct_number);
                all_scores->size = struct_number;

                if (all_scores != NULL) {
                    counters_iterate(scores, all_scores, doc_score_helper);
                    //printf("%d is struct number\n", struct_number);
                    //all_scores = sorted_scores(all_scores, struct_number);
                    
        
                    struct_print(all_scores, struct_number, directory);
                }
                free(all_scores);
            }
            

            //counters_delete(scores);
        
        }
        printf("exited running sum\n");
        
        free(query);
        for (int i = 0; i < *number_of_elements; i++) {
            free(arranged_words[i]);
        }
        *number_of_elements = 0;
        printf("deleted\n");
        free(arranged_words);        
        fprintf(stdout, "Query?");
        
    }
    return 0;
}

//helper function to put the items in the struct array in decreasing
void doc_score_helper(void* arg, const int key, const int count){
    doc_array_t* all_scores = arg; 
    int i = 0;
    for (int i = 0; i < all_scores->size; i++) {
        all_scores->array[i]->ID = key;
        //printf("id %d", all_scores->array[i]->ID);
        all_scores->array[i]->score = count;
    }
    

}

//helper method to get the size of the counters generated after the accumulation algorithm
void doc_score_count_help(void* arg, const int key, const int count){
    int* score = arg;
    (*score)++;
    //printf("score: %d", *score);
}

doc_array_t* sorted_scores(doc_array_t* all_scores, int struct_number){
    for (int i = 0; i < struct_number-1; i++){
        //printf("outerloop\n");
        for (int j = 1; j < struct_number; j++){
            //printf("inner\n");
            //printf("star %d\n", (all_scores->array[i]->score));
            //printf("%d\n", all_scores->array[i]->score);
            if (all_scores->array[i]->score < all_scores->array[j]->score){
                //saving j
                int saved_score_j = all_scores->array[j]->score;
                int saved_ID_j = all_scores->array[j]->ID;

                printf("saved_score is: %d\n", saved_score_j);

                //saving i
                int saved_score_i = all_scores->array[i]->score;
                int saved_ID_i = all_scores->array[i]->score;

                //moving i to j
                all_scores->array[j]->score = saved_score_i;
                all_scores->array[j]->ID = saved_ID_i;

                //moving saved j to i
                all_scores->array[i]->score = saved_score_j;
                all_scores->array[i]->ID = saved_ID_j;
                
            }
        }

    }
    return all_scores;
}

//function to print a clean query
void clean_query (char** query, int number){
    printf("Query: ");
    for (int i = 0; i < number; i ++){
        printf("%s ", query[i]);
    }
    printf("\n");
    
}

//function to print the result 
void struct_print(doc_array_t* all_scores, int struct_number, char* directory){
    printf("Matches %d documents (unranked)\n", struct_number);
    for (int i = 0; i < struct_number; i++){
        int k = 1; 
        printf("score: %d Document: %d: ", all_scores->array[i]->score, all_scores->array[i]->ID);
        char* temp_direc = malloc(strlen(directory)+ sizeof (struct_number) + sizeof(char*));
        sprintf(temp_direc, "%s/%d", directory, (all_scores->array[i]->ID));
        //printf("%s\n", temp_direc);
        printf("\ntemp direc is %s\n", temp_direc);

        FILE* fp;
        fp = fopen(temp_direc, "r");
        char* url; 
        if (pagedir_validate(temp_direc)){
            url = freadlinep(fp);
            printf("%s\n", url);
            fclose(fp);
            free(url);
        }
        free(temp_direc);
        
      
    }
    printf("-----------------------------------------------------------\n");


}

