CC=gcc
CFLAGS=-I. -std=c11 -pthread
SFLAGS=-lfactor -L.
FPFlags=-fPIC -c

all: client server

again: clean all

server: libfactor
	$(CC) -o server server.c  $(CFLAGS) $(SFLAGS)

client: libfactor
	$(CC) -o client client.c  $(CFLAGS) $(SFLAGS)

libfactor: factor.o
	$(CC) -shared -o libfactor.so factor.o $(CFLAGS)

factor.o: factorial.c factorial.h
	$(CC) -o factor.o factorial.c $(CFLAGS) $(FPFlags)

clean:
	rm factor.o libfactor.so client server ips.md