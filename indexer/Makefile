# Makefile for indexer
#
# Taken largely from the makefile in crawler
# Brian Yu
# 10/22/21

#shortcut for directory
L = ../libcs50
C = ../common

OBJS = indexer.o
LIBS = 
LLIBS = $C/common.a $L/libcs50-given.a 

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L -I$C
CC = gcc
MAKE = make 
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

indexer: indexer.o 
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o $@

indextest: indextest.o
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o $@

indexer.o: $L/hashtable.h $L/file.h $L/webpage.h $C/pagedir.h $C/index.h $C/word.h

indextest.o: $L/hashtable.h $L/file.h $L/webpage.h $C/pagedir.h $C/index.h $C/word.h


.PHONY: all test valgrind clean

all: indexer indextest
# expects a file `test.names` to exist; it can contain any text.
test: indexer
	bash -v testing.sh &> testing.out

# expects a file `test.names` to exist; it can contain any text.
#valgrind: hashtabletest test.names
#	$(VALGRIND) ./hashtabletest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f indexer
	rm -f indextest