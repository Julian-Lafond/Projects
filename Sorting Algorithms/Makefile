CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic 

.PHONY: all clean 

all: sorting


sorting: sorting.o insert.o heap.o quick.o shell.o stats.o
	$(CC) $(CFLAGS) -o sorting sorting.o insert.o heap.o quick.o shell.o stats.o -lm

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

clean: 
	rm -f *.o sorting

format:
	clang-format -i -style=file *.h *.c

scan-build: clean
	scan-build make

