CFLAGS=-Wall -Wextra -Werror -Wpedantic
CC=clang $(CFLAGS)

tower   :	tower.o	
	$(CC) -o tower tower.o stack.o
tower.o :	tower.c
	$(CC) -c tower.c stack.c
all	:
	$(CC) -c tower.c stack.c
	$(CC) -o tower tower.o stack.o
clean   :
	rm -rf tower tower.o stack.o infer-out
infer   :
	make clean; infer-capture -- make; infer-analyze -- make
format  :
	clang-format -i -style=file *.c

