# Brian Yu, CS50, indexer testing.md
## Comparing the output from indexer.c and indextest.c

### I did not leverage indexsort.awk
* Comparing the two files to make sure that they are identical
* result is the product of indexer and result2 is the product of indextest.
1. result: include 2 2 3 1 ; result2: 2 2 3 1
2. result: constant 2 13 3 19 ; result2: constant 2 13 3 19
3. result: wikimediafoundation 2 1 3 1 ; result2: wikimediafoundation 2 1 3 1
4. result: wikipedia 1 6 2 13 3 11 ; result2: wikipedia 1 6 2 13 3 11

### Excluding the order of the words, the two files are identical. 