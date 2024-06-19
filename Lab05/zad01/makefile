GCC = gcc
CFLAGS = -Wall

all: signalReact
.PHONY: test clean

signalReact: signalReact.c 
	$(GCC) $(CFLAGS) -o signalReact signalReact.c

test: signalReact
	@echo -Test none-
	-./signalReact none
	@echo -Test ignrowania-
	-./signalReact ignore
	@echo -Test handlera-
	-./signalReact handler
	@echo -Test maski-
	-./signalReact mask
	@echo -Test nieprawidlowych argumentow-
	-./signalReact ala ma kota

clean:
	rm -f signalReact