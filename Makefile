ifeq ($(debuglevel),1)
	CCFLAGS = -c -O0 -g -Wall -Wextra -pedantic -std=c++11 -DDEBUG_LEVEL=1
else
	CCFLAGS = -c -O2 -Wall -Wextra -pedantic -std=c++11 -DDEBUG_LEVEL=0
endif
C = gcc
CC = g++

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