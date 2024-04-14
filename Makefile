CC=g++
CFLAGS=-O2 -I./testvectors -Wall -Wextra -std=c++11 -pedantic -Wno-long-long -g
BLAKEBINS=blake2b 
SELFTEST=-DBLAKE2B_SELFTEST
# SELFTEST=

all:	$(BLAKEBINS) check

blake2b:	blake2b.cpp
	$(CC) blake2b.cpp -o $@ $(CFLAGS) $(SELFTEST)

check:	blake2b
	./blake2b

test:
	$(CC) $(CFLAGS) -o test test.cpp blake2b.cpp
	# ./test > test-output.h
	gdb test

clean:
	rm -rf *.o test test-output.h $(BLAKEBINS)