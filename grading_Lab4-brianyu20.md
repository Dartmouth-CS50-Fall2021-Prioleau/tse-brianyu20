# Grader: Chahak Goyal

## Total Score: 90/100  

### Delivery: 19/20  

5 points: proper use of git

3 points: Follow the required file structures without extra data files, .o files, backup files, etc...
* -1 for commiting `.crawler`

5 points: Makefiles provided that can build all targets and includes a 'clean' target.

5 points: "make" compiles properly with correct flags, produces `crawler`

2 points: "make clean" does what it should

### Documentation and Testing: 20/22    

4 points has well-written README.md

6 points has well-written IMPLEMENTATION.md
* -2. Please look at the example IMPLEMENTATION.md to see how it is written. It should contain pseudocodes and function prototypes of all functions from all the files you used to make your program.

4 points for well-written testing.sh summarizing representative test cases

2 points documented assumptions

6 points source files and scripts have relevant and necessary comments

### Code Quality: 17/20  

10 points: Well-structured and easy to follow; very readable, with meaningful comments. cohesive and concise.

10 points: Follows [CS50 style](http://www.cs.dartmouth.edu/~cs50/Resources/CodingStyle.html)
* -3 for not checking for NULL return from malloc/calloc.  

### Functionality: 34/38  

5 points for no memory leaks and errors  

33 points for correct output  
* -2 for producing output when depth is negative  
* -2 for producing output when the URL inputted is `https://www.google.com/`. This is because it is not internal seed.  



