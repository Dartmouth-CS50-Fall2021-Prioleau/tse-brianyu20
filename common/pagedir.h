/*
*pagedir.h - headerfile for pagedir module
*Two main functionalities: to check whether the directory exists and is writable
*and to actually write files in the directory. 
*
*Brian Yu
*part of lab 4, crawler
*10/14/21
*/

#include <stdbool.h>
#include "../libcs50/webpage.h"

/**************** functions ****************/

/**************** check_directory ****************/
/**Function to check if the directory exists, and if it's writable
 *Doing so by trying to create a file in it
 * 
 * We return:
 *  true on success (if the directory exists and it's writable)
 *  false if either the directory doens't exist or is not writable
 * 
 */
bool check_directory(char* pageDirectory);

/**************** write_directory ****************/
/**Function to actually write in the directory
 * Doing so by creating the write filename and then 
 * writing in the file according to the lab instructions. 
 * 
*/
void write_directory(char* pageDirectory, webpage_t* page, int ID);

/**************** pagedir_validate ****************/
/**Function to confirm that the directory is a crawler produced directory
 * Simple function.
 * It will try to open a file and if it's successful, it will return true. 
 * otherwise, it will return false.
 * 
 * caller should put in [pagedirectory/.crawler] to check if it's a crawler produced directory 
 * However, this function also works in general to see if a file opens. 
*/
bool pagedir_validate(char* filename);