# Lab 5

### Delivery (20%)

 * 5/5 points: proper use of git (submitted via git, with the right tag)

 * 3/3 points: Follows the required file structures without extra data files, .o files, backup files, etc...

 * 5/5 points: Makefiles provided that can build all targets and includes a 'clean' target.

 * 5/5 points: "make" compiles properly with correct flags, produces 'indexer';

 * 2/2 points: "make clean" does what it should


### Documentation & Testing (22%)

 * 2/4 points: sparse README.md (-2)

 * 6/6 points: well-written IMPLEMENTATION.md 

 * 2/4 points: too few test cases in testing.sh (next time test on creating a variety of different indexes of varying size) (-2)

 * 0/2 points: did not document assumptions (-2)

 * 6/6 points: source files and scripts have relevant and necessary comments

### Code Quality (20%)
  * 10/10 points: Well-structured and easy to follow; very readable, with meaningful comments. cohesive and concise.

  * 10/10 points: Follows [CS50 style](http://www.cs.dartmouth.edu/~cs50/Resources/CodingStyle.html);



### Functionality (38%)

   * 12/12 points: Testing bad inputs

   * 21/21 points: Testing index-creating inputs

   * 0/5 points: Memory leaks in all cases (-5)

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

# Overall: 89/100