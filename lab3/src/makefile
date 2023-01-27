CC=gcc
CFLAGS=-I. -std=c99

all: sequential_min_max parallel_min_max parallel_sequential

parallel_sequential: sequential_min_max parallel_sequential.o
	$(CC) -o parallel_sequential parallel_sequential.o $(CFLAGS)

sequential_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o sequential_min_max find_min_max.o utils.o sequential_min_max.c $(CFLAGS)

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

parallel_sequential.o: 
	$(CC) -o parallel_sequential.o -c parallel_sequential.c $(CFLAGS)

clean :
	rm utils.o find_min_max.o parallel_sequential.o sequential_min_max parallel_min_max parallel_sequential