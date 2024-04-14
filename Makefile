CC=gcc
CFLAGS=-O2 -I../testvectors -Wall -Wextra -std=c89 -pedantic -Wno-long-long
BLAKEBINS=blake2b 

all:	$(BLAKEBINS) check

blake2b:	blake2b.c
	$(CC) blake2b.c -o $@ $(CFLAGS) -DBLAKE2B_SELFTEST

check:	blake2b
	./blake2b

kat:
		$(CC) $(CFLAGS) -o genkat-c genkat-c.c blake2b-ref.c blake2s-ref.c blake2sp-ref.c blake2bp-ref.c blake2xs-ref.c blake2xb-ref.c
		$(CC) $(CFLAGS) -o genkat-json genkat-json.c blake2b-ref.c blake2s-ref.c blake2sp-ref.c blake2bp-ref.c blake2xs-ref.c blake2xb-ref.c
		./genkat-c > blake2-kat.h
		./genkat-json > blake2-kat.json

clean:
		rm -rf *.o genkat-c genkat-json blake2-kat.h blake2-kat.json $(BLAKEBINS)