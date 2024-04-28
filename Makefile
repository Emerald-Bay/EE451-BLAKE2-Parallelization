CC=g++
CFLAGS=-O2 -I./testvectors -Wall -Wextra -std=c++11 -pedantic -Wno-long-long -g
BLAKEBINS=blake2b 
SELFTEST=-DBLAKE2B_SELFTEST
# SELFTEST=

all:	$(BLAKEBINS) check

blake2b-pthread:	blake2b_pthread_test.cpp
	$(CC) blake2b_pthread_test.cpp -o blake2b_pthread $(CFLAGS) $(SELFTEST)

blake2b-opt:	blake2b.cpp
	$(CC) blake2b.cpp -o blake2b $(CFLAGS) $(SELFTEST)

blake2b-serial:	blake2b-serial.cpp
	$(CC) blake2b-serial.cpp -o blake2b-serial $(CFLAGS) $(SELFTEST)

check:	blake2b
	./blake2b

test:
	$(CC) $(CFLAGS) -o test test.cpp blake2b.cpp
	./test

test_par:
	$(CC) $(CFLAGS) -o test_par test.cpp blake2b_pthread_test.cpp -lpthread
	./test_par

test_serial:
	$(CC) $(CFLAGS) -o test_serial test.cpp blake2b_serial.cpp -lpthread
	./test_serial

clean:
	rm -rf *.o test test_par test_serial test-output.h $(BLAKEBINS)