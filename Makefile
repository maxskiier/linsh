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
	@install linsh /usr/bin/linsh
	@echo /usr/bin/linsh | tee -a /etc/shells

	@echo "info: make linsh your standard shell with 'chsh -s /usr/bin/linsh'"
