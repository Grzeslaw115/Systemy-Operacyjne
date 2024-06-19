CC = gcc
CFLAGS = -Wall

all: reverse_c reverse_b
.PHONY: all clean test

reverse_c: reverse.c 
	$(CC) $(CFLAGS) -DCHAR reverse.c -o reverse_c

reverse_b: reverse.c 
	$(CC) $(CFLAGS) reverse.c -o reverse_b

clean:
	rm -f reverse_c reverse_b

test: reverse_c reverse_b
	@echo "Testing reverse by character"
	./reverse_c binary_file.bin tmp1.bin
	./reverse_c tmp1.bin tmp2.bin
	diff -s binary_file.bin tmp2.bin
	rm -f tmp1.bin tmp2.bin
	@echo "Testing reverse by block"
	./reverse_b binary_file.bin tmp1.bin
	./reverse_b tmp1.bin tmp2.bin
	diff -s binary_file.bin tmp2.bin
	rm -f tmp1.bin tmp2.bin