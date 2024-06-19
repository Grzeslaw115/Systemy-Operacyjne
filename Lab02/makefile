CC=gcc
CFLAGS=-Wall

all: static shared dynamic
.PHONY: all clean test

# Tworzenie biblioteki statycznej z rozszerzeniem .a
libcollatz.a: collatz.o
	$(CC) -c collatz.c -o collatz.o
	ar rcs libcollatz.a collatz.o

# Tworzenie biblioteki współdzielonej z rozszerzeniem .so (shared object)
libcollatz.so: collatz.o
	$(CC) -shared -fPIC collatz.o -o libcollatz.so

# Tworzenie programow z uzyciem roznych bibliotek
static: libcollatz.a
	$(CC) $(CFLAGS) client.c -L. -lcollatz -o client_static

shared: libcollatz.so
	$(CC) $(CFLAGS) client.c -L. -lcollatz -Wl,-rpath,$(PWD) -o client_shared

dynamic: libcollatz.so
	$(CC) $(CFLAGS) -DDYNAMIC client.c -ldl -o client_dynamic

# Czyszczenie plików
clean:
	rm -f *.o *.a *.so client_static client_shared client_dynamic

# Testowanie programow
test:
	./client_dynamic
	./client_shared
	./client_static