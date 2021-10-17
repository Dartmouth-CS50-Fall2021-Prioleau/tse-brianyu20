# Makefile for crawler
#
# Taken largely from the makefile in Bag
# Brian Yu
# 10/14/21

#shortcut for directory
L = ../libcs50
C = ../common

OBJS = crawler.o
LIBS = 
LLIBS = $L/libcs50-given.a $C/common.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L -I$C
CC = gcc
MAKE = make 
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

crawler: $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

crawler.o: $L/bag.h $L/hashtable.h $L/webpage.h $L/memory.h $L/file.h $C/pagedir.h


.PHONY: all test valgrind clean

all: crawler
# expects a file `test.names` to exist; it can contain any text.
test: crawler
	bash -v testing.sh &> testing.out

# expects a file `test.names` to exist; it can contain any text.
#valgrind: hashtabletest test.names
#	$(VALGRIND) ./hashtabletest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f crawler

