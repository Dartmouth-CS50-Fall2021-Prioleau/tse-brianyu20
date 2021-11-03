# Lab 5

-2 only 3 unit tests

## (7/10) Overall
  * 0/3 Proper git tag.

  * 2/3 git commit history - logical groupings of changes in each commit, and meaningful commit messages.

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


## (6/10) Testing

  * 4/8 `tse/indexer/testing.sh` should have good test cases and good comments
    * too few test cases in testing.sh (next time test on creating a variety of different indexes of varying size) 
    * does not test indextest.c
  * 2/2 `tse/indexer/testing.out` should be the output of `make test &> testing.out`


## (20) Coding Style
  * 20/20 Follows [CS50 C program coding style](http://www.cs.dartmouth.edu/~cs50/Resources/CodingStyle.html).


## (6/30) Functionality
  * 6/6 Validation of command-line arguments in both `indexer` and `indextest`.
  * 0/16 Correct outputs on a variety of test cases - compare with solution `indexer` and `indextest`.
  	* segfaults on our test cases
  	* fails your test case
  * 0/8 `indextest` properly loads and saves the index and they've demonstrated (through testing) that the output index is equivalent to the input index.


## (6/10) Memory leaks, according to valgrind
for both `indexer` and `indextest`.

  * 0/4 free of *memory errors*.
  * 2/4 free of *lost memory blocks*.
    * Memory leak in the case of a bad pagedir or index file input (file not writable or directory not readable).

Command: ./indexer ../../lab5-soln/indexer/data/tse-output//toscrape-depth-1/ testing.index2
```C
	==686== 
	==686== Invalid write of size 1
	==686==    at 0x4C34E00: strcpy (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
	==686==    by 0x10946B: main (indexer.c:48)
	==686==  Address 0x522f0d4 is 0 bytes after a block of size 4 alloc'd
	==686==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
	==686==    by 0x10944D: main (indexer.c:47)
	==686== 
	==686== Invalid write of size 1
	==686==    at 0x4C34E0D: strcpy (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
	==686==    by 0x10946B: main (indexer.c:48)
	==686==  Address 0x522f0de is 10 bytes after a block of size 4 alloc'd
	==686==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
	==686==    by 0x10944D: main (indexer.c:47)
	==686== 
	==686== Syscall param openat(filename) points to unaddressable byte(s)
	==686==    at 0x4F4DD5E: open (open64.c:47)
	==686==    by 0x4ECA659: _IO_file_open (fileops.c:189)
	==686==    by 0x4ECA659: _IO_file_fopen@@GLIBC_2.2.5 (fileops.c:281)
	==686==    by 0x4EBCF89: __fopen_internal (iofopen.c:78)
	==686==    by 0x4EBCF89: fopen@@GLIBC_2.2.5 (iofopen.c:89)
	==686==    by 0x10996D: pagedir_validate (pagedir.c:70)
	==686==    by 0x109495: main (indexer.c:56)
	==686==  Address 0x522f0d4 is 0 bytes after a block of size 4 alloc'd
	==686==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
	==686==    by 0x10944D: main (indexer.c:47)
	==686== 
	couldn't read the file
	directory or file is wrong
	==686== 
	==686== HEAP SUMMARY:
	==686==     in use at exit: 0 bytes in 0 blocks
	==686==   total heap usage: 508 allocs, 508 frees, 9,268 bytes allocated
	==686== 
	==686== All heap blocks were freed -- no leaks are possible
	==686== 
	==686== For counts of detected and suppressed errors, rerun with: -v
	==686== ERROR SUMMARY: 12 errors from 3 contexts (suppressed: 0 from 0)
```
    
  * 2/2 free of *still reachable* memory blocks.


  # Overall: 63/100
