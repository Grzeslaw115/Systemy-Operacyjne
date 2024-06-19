GCC = gcc 
CFLAGS = -Wall

.PHONY: all clean
all: client printer

client: client.c
	$(GCC) $(CFLAGS) -o client client.c -lrt -lpthread
	
printer: printer.c
	$(GCC) $(CFLAGS) -o printer printer.c -lrt -lpthread

clean:
	rm -f client printer 