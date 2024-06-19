GCC = gcc
CFLAGS = -Wall

all: client server

client: client.c
	$(GCC) $(CFLAGS) -o client client.c -lpthread

server: server.c
	$(GCC) $(CFLAGS) -o server server.c -lpthread

clean:
	rm -f client server