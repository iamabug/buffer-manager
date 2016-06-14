CC = clang
OBJ = file.o buffer.o init.o

buffer-manager : file.o buffer.o
	@echo compling buffer-manager
	@CC -o buffer-manager file.o buffer.o

init : init.o file.o
	@echo compling init
	@CC -o init init.o file.o

file.o : common.h file.h
buffer.o : common.h buffer.h
init.o : common.h init.h file.h

.PHONY : cleaninit clean
cleaninit:
	@echo clean init
	@rm init init.o file.o

clean:
	@echo clean all
	@rm init buffer-manager $(OBJ)

