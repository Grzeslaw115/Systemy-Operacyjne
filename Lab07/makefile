CC = gcc
CFLAGS = -Wall

all: client server

client_key_file:
	touch client_key_file

server_key_file:
	touch server_key_file

client: client_key_file client.c
	$(CC) $(CFLAGS) -o client client.c

server: server_key_file server.c
	$(CC) $(CFLAGS) -o server server.c

clean:
	rm -f client server client_key_file server_key_file