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
	@printf "\033[32msuitable SBC names:\033[0m\n"
	@printf "RPI_V1\n"
	@printf "RPI_V2\n"
	@printf "RPI_V3\n"
	@printf "supported targets:\n"
	@printf "\033[32mall\033[0m: compile all\n"
	@printf "\033[32minstall\033[0m: compile all\n"
	@printf "\033[32minstall_systemd\033[0m: install service files\n"
	@printf "\033[32mrun\033[0m: run from current folder\n"
