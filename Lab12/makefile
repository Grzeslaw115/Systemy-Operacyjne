GCC = gcc 
CFLAGS = -Wall

all: server client
.PHONY: all clean

server: server.c
	$(GCC) $(CFLAGS) -o server server.c -lpthread

client: client.c
	$(GCC) $(CFLAGS) -o client client.c -lpthread

clean:
	rm -f server client