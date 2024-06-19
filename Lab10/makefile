GCC = gcc 
CFLAGS = -Wall

all: santa
.PHONY: all clean test

santa: santa.c
	$(GCC) $(CFLAGS) santa.c -o santa

clean:
	rm -f santa