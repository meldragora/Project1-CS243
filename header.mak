
# any warning will be considered a compiler error.
CFLAGS =	-ggdb -std=c99 -Wall -Wextra -pedantic -Werror
CLIBFLAGS =	-lm -lbsd
	gcc $(CFLAGS) -c node_heap.c
	gcc $(CFLAGS) -c VLC.c
	gcc $(CFLAGS) -o VLC VLC.o node_heap.o

