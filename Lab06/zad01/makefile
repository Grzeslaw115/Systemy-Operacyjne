GCC = gcc
CFLAGS = -Wall

all: calculateIntegral
.PHONY: all test clean

calculateIntegral: calculateIntegral.c
	$(GCC) $(CFLAGS) -o calculateIntegral calculateIntegral.c

test: calculateIntegral
	./calculateIntegral 0.000000001 1
	./calculateIntegral 0.000000001 10

clean:
	rm -f calculateIntegral results raport_czasowy.txt