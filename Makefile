required_files := main/*.c lib/*.c
required_obj := *.o
include_dir := include/
flags := -Wall -I$(include_dir)

all: _obj_comp
	cc $(required_obj) -o linsh

_obj_comp:
	cc $(flags) -c $(required_files)