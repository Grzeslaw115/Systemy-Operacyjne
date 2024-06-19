GCC = gcc
CFLAGS = -Wall

all: sender catcher
.PHONY: all clean

catcher: catcher.c
	$(GCC) $(CFLAGS) catcher.c -o catcher

sender: sender.c
	$(GCC) $(CFLAGS) sender.c -o sender

clean:
	rm -f sender catcher