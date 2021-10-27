# Brian Yu, CS50 lab 5, indexer Design spec
## User Interface
* it must have three arguments in the following format

```./indexer pageDirectory filename```
* where the pageDirectory is the crawler produced directory and the filename is the file that the user wants to save the index into.

## Inputs and Outputs
* the only input is the command line as specified in the User Interface section
* the output that is saved in the filename goes as following:
1. one line per word, one word per line
2. each line provides the word and one or more (docID, count) pairs, in the format: word (docID count) (docID count) …
3. the word and integer is separated by a space

## Functional Decomposition into Modules
* following modules and functions are expected:
1. main; parsing commandline, verifying that all arguments are valid. Then, the main function calls index_build and index_save
2. index_build; reads the directory produced by crawler and builds it into an index struct
3. index.c - index_save; reads into the index struct built by index_build and saves the information in the filename

* following modules are used to help
1. hashtable.h
2. counters.h
3. file.h 
4. pagedir.h


## Pseudo code for logic/algorithmic flow
* indexer will run as the following:
1. parse commandline as shown in user interface
2. for each file in the directory marked with incremented integer,
3. Use functions in file.h to save the first line (url) into a variable, save the second line (depth) to another variable, and the rest into a third variable. 
4. use those variables to create a new webpage, in order to leverage the function getNextWord 
5. read each word of that file
6. if that word hasn't been seen before, make a new entry in the indexer with, initialize a counter for that word and save both the word and counters in that entry
7. if the word has been seen before, simply increment the count the counters of that word. 
8. after the index is built, use index_save to save it to the filename given in the argument 
9. index_save uses two helper functions; one to iterate over the hashtable, and for each hashtable, iterate over each counters. 
10. Nested iteration will help index_save save the information into the filename as the output specified above. 

## Dataflow through modules
1. main validates all arguments. Exit if not valid. 
2. Index is essentially a hashtable. key will be word and the item will be a counters for that word. 
3. functions in pagedir.h are leveraged to check that the arugments are either a valid directory or a valid file. 
4. functions in index.c is leveraged to read into the index that is built through index_build and saves it to the filename given as argument. 

## Major data structures
1. Hashtable (index struct leverages functions in hashtable a lot).
2. Counters
3. Sets
4. Index


## Testing plan
1. Integration testing will take place using a bash script to test various cases to the indexer. 
