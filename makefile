all: gameoflife.c libgol.so
	gcc -o gameoflife -Wall -Wextra -pedantic -std=c11 gameoflife.c libgol.so
libgol.so: gol.c gol.h
	gcc -o libgol.so -fPIC -shared gol.c
clean:
	rm -rf gameoflife gol.o