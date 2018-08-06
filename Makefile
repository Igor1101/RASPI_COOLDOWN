CC ?= cc
SBC ?= RPI_V3
all:
	$(CC) -I ./ -O2  -Wall -D $(SBC) -g -o cooldown  main.c \
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
install_systemd: install
	cp cooldown.service /etc/systemd/system/
	systemctl enable cooldown
help:
	@echo "suitable SBC names:"
	@echo "RPI_V1"
	@echo "RPI_V2"
	@echo "RPI_V3"
