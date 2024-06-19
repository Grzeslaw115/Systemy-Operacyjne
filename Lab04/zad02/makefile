CC = gcc
CFLAGS = -Wall

all: processVariables
.PHONY: clean test

processVariables: processVariables.c
	$(CC) $(CFLAGS) processVariables.c -o processVariables

test: processVariables
	./processVariables .

clean:
	rm -f processVariables