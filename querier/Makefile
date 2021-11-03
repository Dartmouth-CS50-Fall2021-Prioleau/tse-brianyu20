# Makefile for querier
#
# Taken largely from the makefile in indexer
# Brian Yu
# 10/31/21

#shortcut for directory
L = ../libcs50
C = ../common

OBJS = querier.o
LIBS = 
LLIBS = $C/common.a $L/libcs50-given.a 

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L -I$C
CC = gcc
MAKE = make 
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

querier: querier.o 
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o $@


querier.o: $L/hashtable.h $L/file.h $L/webpage.h $L/counters.h $C/pagedir.h $C/index.h $C/word.h 


.PHONY: all test valgrind clean

all: querier 
# expects a file `test.names` to exist; it can contain any text.
test: querier ~/cs50-dev/tse-brianyu20/tw ../result
	bash -v testing.sh &> testing.out

# expects a file `test.names` to exist; it can contain any text.
#valgrind: hashtabletest test.names
#	$(VALGRIND) ./hashtabletest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f querier
