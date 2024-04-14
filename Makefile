CC=gcc
CFLAGS=-O2 -I./testvectors -Wall -Wextra -std=c89 -pedantic -Wno-long-long
BLAKEBINS=blake2b 

all:	$(BLAKEBINS) check

blake2b:	blake2b.c
	$(CC) blake2b.c -o $@ $(CFLAGS) -DBLAKE2B_SELFTEST

check:	blake2b
	./blake2b

test:
	$(CC) $(CFLAGS) -o test test.c blake2b.c
	./test > test-output.h

clean:
	rm -rf *.o test test-output.h $(BLAKEBINS)