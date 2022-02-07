CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all: mathlib-test

e_test: e.o
	$(CC) $(CFLAGS) e.o -o e_test

mathlib-test: mathlib-test.o e.o euler.o bbp.o madhava.o newton.o viete.o
	$(CC) $(CFlags) -o mathlib-test mathlib-test.o e.o euler.o bbp.o madhava.o newton.o viete.o $(LFLAGS)

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c

euler.o: euler.c mathlib.h
	$(CC) $(CFLAGS) -c euler.c

bbp.o: bbp.c mathlib.h
	$(CC) $(CFLAGS) -c bbp.c

madhava.o: madhava.c mathlib.h
	$(CC) $(CFLAGS) -c madhava.c

viete.o:viete.c mathlib.h
	$(CC) $(CFLAGS) -c viete.c

newton.o: newton.c mathlib.h
	$(CC) $(CFLAGS) -c newton.c

clean:
	rm -f e_test mathlib-test *.o *.exe

format: 
	clang-format -i -style = file *.c *.h

scan -build: clean
	scan -build make


