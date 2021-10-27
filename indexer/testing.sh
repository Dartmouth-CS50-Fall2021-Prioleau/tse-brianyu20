#!/bin/bash
# Brian Yu
# 10/23/21
# Purpose: testing file for indexer. 
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
./indexer

# 2 arguments
./indexer directory

#  correct number of argument but invalid directory
./indexer invalidDirectory indexFilename

# correct number of argument but invalid file
./indexer directory invalidfilename

######################################
### These tests should pass ####

./indexer ~/cs50-dev/tse-brianyu20/tw ./result

# see testing.md for a comparison between the file produced by indexer and indextest

