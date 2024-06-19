CXX=gcc
CFLAGS=-Wall

.PHONY: all countdown clean

all: countdown

countdown: countdown.c
	$(CXX) $(CFLAGS) countdown.c -o countdown

clean:
	rm -f countdown
