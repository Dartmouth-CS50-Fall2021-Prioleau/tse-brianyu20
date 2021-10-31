# Lab 5

## (10) Overall
  * 3/3 Proper git tag.

  * 3/3 git commit history - logical groupings of changes in each commit, and meaningful commit messages.

  * 3/3 tse directory and subdirectories `indexer` and `common` exist, and `indexer` must include appropriate `.gitignore`.  

  * 2/2 no executable files, object files, core dump files, editor backup files, or extraneous files existing in any directory.

## (10) Makefiles
  * 4/4 `indexer/Makefile`
	  * 1/1 has proper targets to build `indexer` and `indextest`
	  * 1/1 uses CS50 standard CC flags.
	  * 1/1 has an appropriate `clean` rule.
	  * 1/1 has an appropriate `test` rule.
  * 3/3 directory `common/` exists; `common/Makefile`
	  * 1/1 has proper targets to build `common.a`
	  * 1/1 uses CS50 standard CC flags.
	  * 1/1 has an appropriate `clean` rule.
  * 3/3 Builds `indexer` and `indextest` with no compilation errors or warnings *when compiled from the top-level directory*.

## (10) Documentation


In `tse/indexer/`,

  * 1/1 `README.md`, how to build `indexer`.
  * 4/4 `DESIGN.md`, the abstract design of the indexer with no language-specific details.
  * 3/3 `IMPLEMENTATION.md`: describes the implementation of `indexer`.
  * 2/2 `testing.sh` present and functional with good comments


## (10) Testing

  * 4/8 `tse/indexer/testing.sh` should have good test cases and good comments
    * too few test cases in testing.sh (next time test on creating a variety of different indexes of varying size) (-4)
  * 2/2 `tse/indexer/testing.out` should be the output of `make test &> testing.out`


## (20) Coding Style
  * 20/20 Follows [CS50 C program coding style](http://www.cs.dartmouth.edu/~cs50/Resources/CodingStyle.html).


## (30) Functionality
  * 6/6 Validation of command-line arguments in both `indexer` and `indextest`.
  * 16/16 Correct outputs on a variety of test cases - compare with solution `indexer` and `indextest`.
  * 8/8 `indextest` properly loads and saves the index and they've demonstrated (through testing) that the output index is equivalent to the input index.


## (10) Memory leaks, according to valgrind
for both `indexer` and `indextest`.

  * 4/4 free of *memory errors*.
  * 2/4 free of *lost memory blocks*.
    * Memory leak in the case of a bad pagedir or index file input (file not writable or directory not readable).

```
==16280== HEAP SUMMARY:
==16280==     in use at exit: 40,939 bytes in 488 blocks
==16280==   total heap usage: 982 allocs, 494 frees, 55,528 bytes allocated
==16280== 
==16280== LEAK SUMMARY:
==16280==    definitely lost: 36 bytes in 2 blocks
==16280==    indirectly lost: 0 bytes in 0 blocks
==16280==      possibly lost: 0 bytes in 0 blocks
==16280==    still reachable: 40,903 bytes in 486 blocks
==16280==         suppressed: 0 bytes in 0 blocks
==16280== Rerun with --leak-check=full to see details of leaked memory
==16280== 
==16280== For counts of detected and suppressed errors, rerun with: -v
==16280== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
    
  * 2/2 free of *still reachable* memory blocks.


  # Overall: 94/100