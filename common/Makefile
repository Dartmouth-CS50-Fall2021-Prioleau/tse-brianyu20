# Makefile for crawler
#
# Taken largely from the makefile in Bag
# Brian Yu
# 10/14/21

#shortcut for directory
L = ../libcs50

OBJS = pagedir.o word.o index.o
LIB = common.a
LLIBS = $L/libcs50-given.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L
CC = gcc
MAKE = make 
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

$(LIB): $(OBJS)
			ar cr $(LIB) $(LLIBS) $(OBJS) 

pagedir.o: pagedir.h $L/webpage.h $L/file.h 
word.o: word.h
index.o: $L/hashtable.h $L/counters.h index.h

.PHONY: all test valgrind clean

all: pagedir
# expects a file `test.names` to exist; it can contain any text.
#test: hashtabletest
#	./hashtabletest > testing.out

# expects a file `test.names` to exist; it can contain any text.
#valgrind: hashtabletest test.names
#	$(VALGRIND) ./hashtabletest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o


