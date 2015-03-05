#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "node_heap.h"

int main(int argc, char * argv[])
{
	//start off by creating the heap and reading the symbols:
    Symbol syms[NSYMS];
    int numsyms = read_symbols(NSYMS, syms[]);
    Heap * heap;
    heap_init(heap);
    heap_make( heap, numsyms, syms[] );

    for( int i = 0; i < NSYMS; ++i)
    {
    	printf( "%c %d\n", heap->array[i].syms[0].symbol, heap->array[i].frequency);
    }



    return EXIT_SUCCESS;
}
