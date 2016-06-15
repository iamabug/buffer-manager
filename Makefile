cc = /usr/bin/clang-3.6
OBJ = file.o buffer.o init.o main.o

manager : file.o buffer.o main.o
	@echo compling buffer-manager
	@cc -o manager file.o buffer.o main.o

init : init.o file.o
	@echo compling init
	@cc -o init init.o file.o

file.o : common.h file.h
buffer.o : common.h buffer.h
init.o : common.h init.h file.h
main.o : common.h init.h file.h

.PHONY : cleaninit clean
cleaninit:
	@echo clean init
	@rm init init.o file.o

clean:
	@echo clean all
	@rm init buffer_manager $(OBJ)

