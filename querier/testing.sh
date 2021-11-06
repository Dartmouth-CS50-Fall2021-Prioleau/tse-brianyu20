#!/bin/bash
# Brian Yu
# 10/31/21
# Purpose: testing file for querier. 
# Usage: bash -v testing.sh

#Defining variables
directory=~/cs50-dev/tse-brianyu20/tw
indexFilename=../result
newIndexFilename=../result2

invalidDirectory=this/is/not/valid
invalidfilename=iaminvalid

#####################################
### These tests should fail ###

#1 argument
./querier

# 2 arguments
./querier directory

#  correct number of argument but invalid directory
./querier invalidDirectory indexFilename

# correct number of argument but invalid file
./querier directory invalidfilename

######################################
### These tests will keep prompting the user ####



#start with and 
./querier  ~/cs50-dev/tse-brianyu20/tw ../result < testing

./querier  ~/cs50-dev/tse-brianyu20/tw ../result < testing2

./querier  ~/cs50-dev/tse-brianyu20/tw ../result < testing3

./querier  ~/cs50-dev/tse-brianyu20/tw ../result < testing4

./querier  ~/cs50-dev/tse-brianyu20/tw ../result < testing5


<< EOF
#start with or
echo or include

#double and
echo include and and library

#double or
echo include or or library

#double or and
echo include or and library

#double and or
echo incldue and or library

#ends with and
echo include and

#ends with or
echo include or

#it will start working
#these three should be same 
echo include and library
echo include library
echo library and include

#this shows and precedence
echo include and library or takes
echo include or library and takes


