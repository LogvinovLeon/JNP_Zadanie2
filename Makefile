C = gcc
CC = g++
CCFLAGS = -c -Wall -Wextra -pedantic -std=c++11 -DDEBUG_LEVEL=$(debuglevel)
CFLAGS = $(CCFLAGS)

all: strset_test1

strset_test1: strset_test1.o strset.o strsetconst.o
	$(CC) strset_test1.o strset.o strsetconst.o -o strset_test1

.c.o:
	$(C) $(CFLAGS) $< -o $@

.cc.o:
	$(CC) $(CCFLAGS) $< -o $@

clean:
	rm -rf *.o strset_test1