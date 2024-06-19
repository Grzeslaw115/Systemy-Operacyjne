CC = gcc
CFLAGS = -Wall

all: processCreator
.PHONY: clean test

processCreator: processCreator.c
	$(CC) $(CFLAGS) processCreator.c -o processCreator

test: processCreator
	./processCreator 2

clean:
	rm -f processCreator