required_files := main/*.c lib/*.c
required_obj := *.o
include_dir := include/
flags := -Wall -I$(include_dir) -std=gnu23

CC = gcc

all: _obj_comp
	$(CC) $(required_obj) -o linsh

_obj_comp:
	$(CC) $(flags) -c $(required_files)

install:
	@if [ "$$(whoami)" = "root" ]; then \
		echo "warning: bypassing user check, user is root"; \
		install linsh /usr/bin/linsh; \
		echo /usr/bin/linsh | tee -a /etc/shells; \
	else \
		echo "info: user is NOT root, using sudo"; \
		sudo install linsh /usr/bin/linsh; \
		echo /usr/bin/linsh | sudo tee -a /etc/shells; \
	fi

	@echo "info: make linsh your standard shell with 'chsh -s /usr/bin/linsh'"
