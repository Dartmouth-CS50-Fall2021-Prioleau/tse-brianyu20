/* Brian Yu
*Lab 4, crawler
*10/13/21
*Usage: ./crawler seedURL pageDirectory maxDepth
*Purpose: crawler will start at the seed URL, parse the page and save it to a unique file. Until maxdepth is reached,
*it will fetch all connected URLs to the current URL, and save those pages to a unique file in the pageDirectory. 
*Additional Notes: 
*save_page was taken from class activity. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../libcs50/bag.h"
#include "../libcs50/hashtable.h"
#include "../libcs50/webpage.h"
#include "../libcs50/memory.h"
#include "../libcs50/file.h"
#include "../common/pagedir.h"

/**************** local function prototypes ****************/
void crawler(bag_t* bag, hashtable_t* hashtable, char* pageDirectory, int maxDepth);
void pagescanner(bag_t* bag, hashtable_t* hashtable, webpage_t* page);


int main (int argc, char *argv[]){
    //checking if the user gave three arguments
    if (argc != 4){
        fprintf(stderr, "see appropriate usage again\n");
        return 1; 
    }
    //checking if all the arguments that the user gave are valid
    for (int i = 0; i < 4; i++){
        if (argv[i] == NULL){
            fprintf(stderr, "Not all arguments are valid\n");
            return 1;
        }
    }

    //memory is allocated for bag struct
    bag_t* new_bag = bag_new();

    //memory is allocated for webpage struct
    char* u = (char*) malloc(strlen(argv[1])+10);
    strcpy(u, argv[1]);
    webpage_t* new_page = webpage_new(u, 0, NULL);

    //memory is allocated for hashtable
    hashtable_t* new_hashtable = hashtable_new(300);

    //allocating memory to store the directory name 
    char* directory = (char*)malloc(strlen(argv[2])+10);
    strcpy(directory, argv[2]);
    printf("%s is the directory right now\n", directory);
    
    //arbitrary string to put into the hashtables
    void* any_item = "URL";

    //variable to store the maxdepth
    int d = atoi(argv[3]);


    //if it can fetch it, insert the page into the bag and the url into the hashtable
    if (webpage_fetch(new_page)){
        const char* url = webpage_getURL(new_page);
        bag_insert(new_bag, new_page);
        hashtable_insert(new_hashtable, url, any_item);
    }
    else{
        fprintf(stderr, "couldn't fetch the webpage");
        return 1;
    }

    //calling crawler
    crawler(new_bag, new_hashtable, directory, d);
    
    free(directory);
    
    return 0;
}


void crawler(bag_t* bag, hashtable_t* hashtable, char* pageDirectory, int maxDepth){
    
    //declaring variables to be used in the loop
    webpage_t* extracted;
    int i = 1;

    //until the bag is empty
    while ((extracted = bag_extract(bag)) != NULL){
        //take one page out of the bag
        
        //use pagesaver 
        if (check_directory(pageDirectory)){
            write_directory(pageDirectory, extracted, i);
            i++;
        }
        else{
            fprintf(stderr, "%s is not a directory\n", pageDirectory);
        }
    
        //if it hasn't reached the argument-specified depth
        if (webpage_getDepth(extracted) < maxDepth){
            pagescanner(bag, hashtable, extracted);          
        }
        webpage_delete(extracted);
        //if it didn't enter the maxDepth loop, the page will be extracted and so not in the bag anymore.        
    }  
    hashtable_delete(hashtable, NULL);
    bag_delete(bag, webpage_delete);

}

//function to get all the next urls and then make the webpage from the URL. 
void pagescanner(bag_t* bag, hashtable_t* hashtable, webpage_t* page){
    int pos = 0;
    char* result;

    //taken from the example in the webpage.h function description of getNext URL        
    while ((result = webpage_getNextURL(page, &pos)) != NULL){
        if (NormalizeURL(result) && IsInternalURL(result)){
            if (hashtable_insert(hashtable, result, "URL")){ 
                char* new_result = malloc(strlen(result)+1);
                strcpy(new_result, result);
                //create the new webpage to put into the bag
                webpage_t* adding_new = webpage_new(new_result, (webpage_getDepth(page)+1), NULL);

                //need to get the html 
                if(webpage_fetch(adding_new)){
                    bag_insert(bag, adding_new);
                }       
            }     
        }   
        free(result);            
    } 

}

