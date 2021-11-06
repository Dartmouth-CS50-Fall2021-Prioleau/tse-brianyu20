# Brian Yu, CS50 lab 5, indexer implementation spec

## Pseudocode
### modules & functions
* indexer - index_build:
1. initialize varibales; Doc ID to use to parse through the incremented docs in the pageDirectory, and directory_ID to concatentate the pageDirectory and the doc ID. 
2. Use the pagedir_validate function in the pagedir.h module to loop through all the documents. Because pagedir_validate is returns a boolean whether the filname is open-able, it will exit loop when the concatenated document_ID is not a valid document anymore. 
3. Parse through each document. 
4. When parsing, leverage functions in the file.h module to get to the third line. Save the first two lines in a variable to pass in as parameters to create a new webpage struct. 
5. The webpage struct is made to leverage webpage_getNextWord.
6. For each word in the document, check whether that word is longer than 3 letters and then normalize it using normalize_word function in the word.h module. 
7. If it's the first time that the word is seen, create a new entry. 
8. If the word has been seen before, simply increment the counters associated with it. 
9. Leverage index_save to save the index to a file. 

* index_save
1. index_save actually uses two iterators, one iterater through the hashtable, and another iterator to go through all the counters in a slot of a hashtable. 
2. index_save calls hashtable_iterate. the function called in as a parameter is itemprint.
3. itemprint calls counters_iterate, which leverages counters_itemprint. 
4. In a way, it's a nested iterator; the nested iterator idea is used to save the index into the file in the format given in the requirement and the design spec. 

## function prototypes and parameters
### indexer.c
```void index_build(char* directory, index_t* index)```

### index.c
```void index_save(char* filename, index_t* index)```

```index_t* index_new(const int numslots)```

```void index_delete(index_t* index)```

```void index_item_delete(void* item)```

```counters_t* index_find(index_t* index, void* key)```

```void index_insert(index_t* index, void* key, void* item)```

```void itemprint(void* arg, const char* key, void* item)```

```void counters_itemprint(void* arg, const int key, const int number)```

```void index_load(char* filename, index_t* index)```

### pagedir.c
```bool check_directory(char* pageDirectory)```

```void write_directory(char* pageDirectory, webpage_t* page, int ID)```

```bool pagedir_validate(char* filename)```

### word.c
```char* normalize_word(char* word)```

## Data structures
### Index
* the index struct holds a hashtable. The index is essentially a hashtable; it holds a word as key and a counters as its item. The counters, for each word, holds the doc ID as a key and the the counter as the item. 

## Error Handling
* On error, the program will return non-zero, print to stderr. 


