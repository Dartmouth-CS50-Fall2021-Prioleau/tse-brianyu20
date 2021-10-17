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