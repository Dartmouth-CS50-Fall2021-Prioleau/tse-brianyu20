# Brian Yu, Design Specs for Querier; 10/29/21; CS50
## User Interface
* User will first type in 
```./querier pageDirectory indexFilename```

* Then the user will be prompted with "Query?" where the user will then type in a sequence of words separated by 'and' or 'or'. The sequence of strings may not start or end with 'and' or 'or'. 

## Inputs and Outputs 
### In addition to the input specidied in the user interface section, there are a couple more things that the user should know about querier. 
1. 'and' has precedence over 'or'
2. ```Dartmouth College``` and ```Dartmouth and College``` are equivalent. 
3. Capitalization does not matter. 
4. Whatever the user types in stdin after he/she is prompted ```Query?``` will then be processed and stdout will print a standardized version of what the user has put in. If it does not match the format as specified above, will print an error message and prompt the user again. 
5. Querier will keep prompting the user until EOF is reached. 
### Output 
* If the user puts in a valid sequence of strings,
1. Querier will print how many documents matched. 
2. Querier will print the score, the doc, and the url of that doc, in that order. 
3. Querier will print the matched docs in ranked order by the score. 

## Pseudo code for logic/algorithmic flow
1. Check if all arguments are valid
2. First need to parse the sentence to recognize each word on its by leveraging ```isalpha``` and ```isspace```. 
3. If the words are not in the right format, print an error message and prompt the user again. 
4. If it is in the right format, start the accumulation algorithm. 
5. Until the program sees an 'if', initiate add-sequence functions.
6. when it does see an if, add the add-sequence to the union. Repeat the process
7. Iterate through the counters created by the accumulation algorithm and add that to the array of structs. 
8. Sort the array. 
9. Keep prompting the user as specified in requirements. 

## Functional Decomposition into Modules
1. main; parse the commandline
2. Accumulator; call appropriate intersect and union functions
3. Prompter; create interactive mode for the user

## Major data structures
1. counters.h
2. typedef struct counters_helper_t
3. typedef struct doc_score;
4. index.h

## Testing plan
1. Integration testing will take place using a bash script to test various cases to the indexer. 
