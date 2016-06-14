CC = clang
OBJ = file.o buffer.o init.o

buffer-manager : file.o buffer.o
	CC -o buffer-manager file.o buffer.o

init : init.o file.o
	CC -o init init.o file.o

file.o : common.h file.h
buffer.o : common.h buffer.o
init.o : common.h init.h file.h

.PHONY : clean
	clean:
	rm buffer-manager init $(OBJ)
