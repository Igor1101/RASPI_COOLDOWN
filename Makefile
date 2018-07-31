CC ?= cc
RPI_VERSION ?=RPI_V3
all:
	$(CC) -O2  -Wall -D $(RPI_VERSION) -g -o cooldown  main.c \
		periph.c -static
run:
	sudo ./cooldown
clean:
	rm cooldown
