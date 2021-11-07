# Grading and Commentary for CS50 Lab 6

## Student: Jae Eun Yu (Brian Yu)

## Grader: Amittai

&nbsp;

### **Final Scores**

-------------------
|Problem|Score|
|:-------|------:|
|Delivery|6/10|
|Makefiles|8/12|
|Documentation|12/12|
|Testing|6/6|
|Code Quality|20/20|
|Functionality|12/30|
|Memory Usage|0/10|
|**TOTAL**|**64**|

**Late Penalty: for 24 Hours: -10**
**FINAL SCORE: 54**

&nbsp;

Take a look at the [solution](./lab6-soln/querier/).

## (6/10) Delivery

* (3) Proper git tag `lab6submit`.
* (0/2) git commit history - logical groupings of changes in each commit, and meaningful commit messages.
  * > Nop.
* (2/3) Proper file structure: tse directory and subdirectories `querier` and `common` exist, and `querier` must include appropriate `.gitignore`.  
  * > You added your `querier` folder's `.gitignore` as `gitignore`, so, obviously, git didn't detect it.
* (+1/2) no executable files, object files, core dump files, editor backup files, or extraneous files existing in any directory.

> `:wq` dummy file submitted.
> Also, compiled binaries (think `querier`) should be in the ignore file! Especially when working collaboratively, it's not guaranteed that jsut because you intuitively ignore some files, others on the team will ignore them / clean up before committing their changes. Anyway, no deduction since file wasn't submitted.

## (8/12) Makefiles

* (+3/4) `querier/Makefile`.
  * (1) exists
  * (+0/1) has proper target to build `querier`.
  * (1) uses standard CFLAGS (or with `c11` changed to `gnu11`).
  * (1) has an appropriate `clean` rule.
  
> `querier` Makefile uses `libcs50-given.a` directly. This is incorrect.
>

* (+4/4) directory `common/` exists and `common/Makefile`.
  * (1) exists.
  * (1) has proper targets to build `common.a`.
  * (1) uses CS50 standard CFLAGS.
  * (1) has an appropriate `clean` rule.

* (+1/4) Builds `querier` (and optionally `fuzzquery`) with no compilation errors or warnings *when compiled from the top-level directory*. -1 point per compile warning (-3 at most).

> Fails to compile from top-level directory because you did not fix the libcs50 Makefile to copy given `libcs50-given.a` into `libcs50.a` **-1**. This is a trivial adjustment! Why didn't you do it?
> Two warnings **-2**:

```text
gcc -Wall -pedantic -std=c11 -ggdb  -I../libcs50 -I../common   -c -o querier.o querier.c
querier.c: In function ‘doc_score_helper’:
querier.c:469:9: warning: unused variable ‘i’ [-Wunused-variable]
  469 |     int i = 0;
      |         ^
querier.c: In function ‘struct_print’:
querier.c:533:13: warning: unused variable ‘k’ [-Wunused-variable]
  533 |         int k = 1;
      |             ^
```

## (12/12) Documentation

~~-1 for each doc written with *no* Markdown syntax.~~

* (2) `README.md`, which says how to build `querier`.
* (4) `DESIGN.md`, which describes the abstract design of the querier with no language-specific details.
* (4) `IMPLEMENTATION.md`: describes the implementation of `querier`.

  > No pseudocode in your design / implementation discussions. Could have been nice!

* (2) `testing.sh`, which may refer to testing results included in a separate file (e.g., testing.out, testing.txt)

## (6/6) Testing

* (5) `tse/querier/testing.sh` should have good test cases and good comments
* (1) `tse/querier/testing.out` should be the output of `make test &> testing.out`

## (20/20) Coding Style

* [CS50 C program coding style](http://www.cs.dartmouth.edu/~cs50/Resources/CodingStyle.html)
* Their querier-specific code should be isolated from the data structure code.
* Their querier code should not 'peek' inside opaque types.
* They *need not* use my [*parse_args*]({{site.lectures}}/parse_args) approach, but *should* have a clean, well-organized code for parsing and validating command-line args that is not interwoven with the overall program flow & logic.
* The code should be rigorous in checking for memory-allocation errors or file I/O methods. They are allowed to use `assertp()` or similar methods to exit when `malloc` or `fopen` or constructors (e.g., index_new()) fails or other sanity checks fail.
* Well-designed code structure
  * avoid deep nested loops or conditional blocks.
  * consistent indentation and spacing.
  * sufficient comments.

## (12/30) Functionality

Refer to the [published rubric](https://www.cs.dartmouth.edu/~cs50/Labs/Lab6/#grading) for the number of points to award for progressive levels of functionality.

However, take off points if

* ~~(-4) Improper validation of command-line arguments.~~
* ~~(-1) Cannot handle empty and blank queries, or mishandles EOF on stdin.~~
* ~~(-5) Incorrect output (or no error message) for invalid test queries. (Note that some "invalid" queries are valid for the lowest functionality level.)~~

### Note: I did 9 valid tests, x2 = 18. The remaining 12 points came from how the program handles invalid / boundary cases. See [grading-official-output](./grading-official-output) for official output using the professor's provided program, and [grading-output](./grading-output) for output using your program. For the specific tests, see [grading.sh](./grading.sh). Reach out if you have any questions about the tests, and *if you can prove that your program produces the correct feedback* then I'll return points for the specific tests you prove. (Also, for that case, reach out if you want access to the Prof's solution!)

#### Failed: **I did not get a single valid output out of your querier. Multiple segmentation faults (which I was keen to make sure weren't from fuzzquer! and valgrind clearly shows your querier is attempting to use uninitialized values repeatedly). I'm open to returning *all* or *some* of the points if you can demonstrate that your querier (the submitted version, obviously) actually works.**

I see you documented that your querier doesn't work. Honestly, you would have been better off using an extra day to fix up your program because functionality is 30% of the score (and 1 day is -10%! Actually, even 2, 3 days and get 80 or 70/100?). Also, you mentioned that you free everything but didn't test. Well, valgrind disagrees. Check the bottom half of [grading-output](./grading-output). You use multiple uninitialized values, and actually do get a segfault or two.

## (0/10) Memory leaks, according to valgrind

See the solution's `querier/Makefile` for a method to test for memory leaks.

* ~~(4) free of *memory errors*.~~ So many memory errors!
* ~~(4) free of *lost memory blocks*.~~ So many lost blocks.
* ~~(2) free of *still reachable* memory blocks.~~ So many still reachable blocks.

See [grading-output](./grading-output) for valgrind output.
