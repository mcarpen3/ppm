CC = gcc
CFLAGS=-Wall -g
LIBS=-lm

view: run test.ppm
	ffplay test.ppm

run: compile
	./pi

compile: pi.c
	$(CC) $(CFLAGS) pi.c -o pi $(LIBS)
