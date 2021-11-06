# Brian Yu, CS50 Lab 6 - querier.c
## Notes and Assumptions
1. querier.c used the same output files that were used in crawler and indexer-  ```~/cs50-dev/tse-brianyu20/tw``` and ```../result```
2. No separate assumptions were made other than the ones that the lab instructions provided. 
## Here are what the program lacks:
1. Didn't have time for memory leak checks. However, if you look at the code, I do free all items that are malloced ore created through module functions. also, in deleting the structs that I created, I do loop through to delete all the inner items also. 
2. Accumulation algorithm works if you see, but I didn't have time to add it to the struct correctly and sort it. If that part worked, the printing would work correctly but because the adding algorithm is work, it prints that it can't find the right document to print the url. 
3. So basically the parsing works and the accumulation works but adding and sorting in doc_arry_t doesn't. 