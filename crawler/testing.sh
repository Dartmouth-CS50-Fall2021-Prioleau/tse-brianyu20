#!/bin/bash
# Brian Yu
# 10/16/21
# Purpose: testing file for crawler. 
# Usage: bash -v testing.sh
# Note: most of the syntax in the beginning taken from the sample testing.sh provided in the lab instructions

# Define variables
seedURL=http://cs50tse.cs.dartmouth.edu/tse/letters/
seedURL2=http://cs50tse.cs.dartmouth.edu/
externalURL=www.google.com
invalidURL=www.thisisgoingtobeinvalid.com
wikiURL=http://cs50tse.cs.dartmouth.edu/tse/wikipedia/
directory=/thayerfs/home/f002vv6/cs50-dev/tse-brianyu20/tw
invalidDirectory=tw

#####################################
### These tests should fail ###

# 1 argument
./crawler

# 2 arguments
./crawler $seedURL

# 3 arguments
./crawler $seedURL $directory

# 4 arguments + externalURL
./crawler $externalURL $directory 2

# 4 arguments + invalid directory 
./crawler $externalURL $invalidDirectory 2

# 4 arguments + nonexistent server
./crawler $invalidURL $directory 2



######################################
### These tests should pass ####

# at depth 0
./crawler $seedURL $directory 0

# at depth 1
./crawler $seedURL $directory 1

# at depth 2
./crawler $seedURL $directory 2

# at the base home page
./crawler $seedURL2 $directory 1

# at the wikipedia page
./crawler $wikiURL $directory 1


