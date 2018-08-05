CC ?= cc
SOC ?= RPI_V3
all:
	$(CC) -I ./ -O2  -Wall -D $(SOC) -g -o cooldown  main.c \
		periph.c -static
run:
	sudo ./cooldown
clean:
	rm cooldown
install: cooldown
	# RUN THIS AS ROOT
	@# Make all dirs needed:
	mkdir -p /etc/cooldown/
	cp cooldown /usr/bin/
	cp config /etc/cooldown
help:
	@echo "suitable SOC names:"
	@echo "RPI_V1"
	@echo "RPI_V2"
	@echo "RPI_V3"
