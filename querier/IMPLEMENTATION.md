# Brian Yu, CS50 lab 5, querier implementation spec

## Pseudocode
### main function
1. validation: checking right number of arguments, checking that they aren't null, directory produced by crawler
2. Call prompter
3. Prompter provides the backbone for the user interface. 
4. It calls ```words``` function, which tokenizes the query given by the user. 
5. The query is tokenized by putting a pointer at the start of the word, and then putting an extra null character when that word ends. The product is a 2D arrray of strings. 
6. Then, the prompter checks if the tokenized 2d string is in format- no repeated conjunctiosn, can't start or end with a conjunction, etc.
7. then, ```running_sum``` is called. 
8. ```running_sum``` goes through the tokesn. Until it sees 'or', it will create an and-sequence. When it sees the or, it will union the andsequence with a set (can be empty) that was initialized before. This will continue until the end of query. 
9. Then, the resulting counters of doc ID and the score is put into an array of structs. Each struct contains an ID and score. Once each doc and score pair is added to the array, it is sorted in decreasing order. 
10. The sorted items are then printed. 

## function prototypes and parameters
```char** words(char* query, int number_of_elements);```

```bool check_words(char** words, int length);```

```bool is_and (char* word);```

```bool is_or (char* word);```

```counters_t* intersection (counters_t* first, counters_t* second);```

```void intersection_helper (void *arg, const int key, const int count);```

```counters_t* Union (counters_t* first, counters_t* second);```

```void union_helper (void*arg, const int key, const int count);```

```counters_t* running_sum(char** words, index_t* index, int number_of_elements);```

```void prompter(index_t* index, int number_of_elements);```

```void doc_score_count_help(void* arg, const int key, const int count);```

```void doc_score_helper(void* arg, const int key, const int count);```

```doc_score_t** sorted_scores(doc_score_t** all_scores, int struct_number);```

```void clean_query (char** query, int number);```


## Data Structures
1. Counters; used to get the word count for each word for each document, but more importantly, it is later used to represent the doc ID and the score for the given query. 
2. struct holding the ID and score is useful in the intersection method 
3. Structy holding the ID and score is useful in sorting algorithm. 

## Error Handling
1. Error cases in the orignial commandline is handled in main. Program will not start. 
2. Wrong format of a query will instruct the user what is wrong with the current formating, and then will promp the user again to provide a valid format query. 