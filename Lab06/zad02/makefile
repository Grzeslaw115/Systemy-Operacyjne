GCC = gcc 
CFLAGS = -Wall

all: calculator reader
.PHONY: all clean

calculator: calculator.c
	$(GCC) $(CFLAGS) -o calculator calculator.c

reader: reader.c
	$(GCC) $(CFLAGS) -o reader reader.c

clean:
	rm -f calculator reader namedPipe