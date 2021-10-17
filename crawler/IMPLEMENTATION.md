# Brian Yu, CS50 Fall 2021, Lab 4, Crawler; Implementation details
## Crawler; purpose and usage
1. crawler, given a seed URL, a directory to save files to, and a depth, will 'crawl' the URL, explore all connected urls to the seed url, and then save the webpage information in a unique file in the given directory. 
2. ./crawler seedURL pageDirectory Depth 

## Implementation Detail
1. Started by checking for argument errors. Because each conditional statments have a non-zero return, if there is an error as specified in the conditional, it will exit. It checks if the user passed in the correct number of arguments, and that the arguments are valid. 
2. Then, the program moves onto initializing various data structures and strings to use in the main function. the '+10's are added to make sure that there's enough space, and the hashtable is allocated 300 slots. The arguments are saved to the initialized variables to make sure that there aren't incompatiblities when they are used in the crawler function. 
3. Before the main function actually calls the crawler function, it initializes the first webpage. This was chosen to do it outside of the crawler function because if the parsed arguments are valid, there will always be a first webpage stored in the bag before crawler performs its function. 
4. Then, crawler is finally called. Details of the crawler function is outlined in the bullet points underneath.
* First take a webpage out of the bag. The logic of the while loop makes it so that the crawler will keep crawling until there are no more pages in the bag to crawl. 
* Then, the crawler utilizes the pagedir module functions. For each page, by leveraging ```bool check_directory(char* pageDirectory)``` and ```void write_directory(char* pageDirectory, webpage_t* page, int ID)``` the crawler writes each webpage to the directory with a unique ID. 
* pagescanner gets all the urls linked to the current webpage, makes sure to normalize and that it is internal to the server. It continues to create a new webpage struct for that url, fetches the HTML, and then adds to the bag again. 
5. There are no memory leaks. 

## Data structures
1. bag
* bag structure was used to hold all the webpages. Because bag is an unordered set of items, the saved pages in the pageDirectory might not print all in the same order, but it will print all because of bag_extract function. 
2. hashtable
* hashtable was used to hold all the URLs. Hashtable was optimal for holding URLs because hashtables don't allow duplicates, and crawler does not want to crawl to same webpage twice if that webpage is referecned by two different sources. 
3. webpage
* webpage holds URL information, HTML, and the depth. URL can simply be saved into the struct, but the HTML has to be inserted through ```webpage_fetch```.  The depth is important, as the incrementation of that dictates which websites are elibible to be inserted into the bag. 


## Notes
1. The implementation was largely based from the design spec provided. The code is well documented with detailed pseudocode within the program itself. 