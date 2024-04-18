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
	$(CC) $(CFLAGS) -o test jack_test.cpp blake2b.cpp
	./test > test-output.h
	#gdb test

test_par:
	$(CC) $(CFLAGS) -o test_par jack_test.cpp blake2b_pthread_test.cpp -lpthread --std=c++20
	./test_par
	# > test-par-output.h

clean:
	rm -rf *.o test test-output.h $(BLAKEBINS)