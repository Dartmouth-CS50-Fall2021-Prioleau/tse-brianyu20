/**
 * indextest.c
 * Program will load the file produced by index.c back into an index structure
 * then, it will save the file to another file. 
 * Usage: ./indextest oldIndexFilename newIndexFilename
 * Purpose: testing indexer.c
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

int main (int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "See appropriate usage again\n");
        return 1; 
    }

    //initializing data structures and variables
    FILE* fp = fopen(argv[1], "r");
    int slots = lines_in_file(fp);
    fclose(fp);

    index_t* index = index_new(slots);

    index_load(argv[1], index);
    index_save(argv[2], index);

    index_delete(index);

    return 0;
}
