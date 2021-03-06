#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "node_heap.h"

///@author Tyler Quesnel

Node combine( Heap * heap )
{
    Node l1, l2;
    l1 = heap_remove(heap);
    l2 = heap_remove(heap);
    Node combine;
    combine.frequency = l1.frequency + l2.frequency;
    combine.num_valid = l1.num_valid + l2.num_valid;
    for(size_t i = 0; i < l1.num_valid; ++i)
    {
      l1.syms[i].codeword[l1.syms[i].bit] = '0';
      --l1.syms[i].bit;
      combine.syms[i] = l1.syms[i];
      /*
      for(int x = l1.syms[i].bit; x < MAX_CODE; ++x)
        printf("%c", l1.syms[i].codeword[x]);
      printf("%c\n", l1.syms[i].symbol);*/
    }
    for(size_t i = 0; i < l2.num_valid; ++i)
    {
      l2.syms[i].codeword[l2.syms[i].bit] = '1';
      --l2.syms[i].bit;
      combine.syms[i + l1.num_valid] = l2.syms[i];
      /*
      for(int x = l2.syms[i].bit; x < MAX_CODE; ++x)
        printf("%c", l2.syms[i].codeword[x]);
      printf("%c\n", l2.syms[i].symbol);*/
    }
    return combine;
}

int main(void)
{
    //start off by creating the heap and reading the symbols:
    Symbol syms[NSYMS];
    int numsyms = read_symbols(NSYMS, syms);
    for(int i; i < numsyms; ++i)
    {
      printf("freq:%zu  ", syms[i].frequency);
      printf("sym:%c\n", syms[i].symbol);
    }
    Heap heap;
    heap_init( &heap );
    heap_make( &heap, numsyms, syms );
    
    //start creating the codes:
    while( heap.size > 1 )
    {
      Node next = combine( &heap );
      heap_add( &heap, next );
    }
    
    //print out the finished codes:
    printf("Variable Length Code Information\n");
    printf("================================\n");
    for( size_t i = 0; i < heap.array[0].num_valid; ++i)
    {
      //the following sequence of if elses determines what the next symbol
      //is and how to print it.
      char c = heap.array[0].syms[i].symbol;
      if(' ' <= c && c <= '~')
        printf("symbol:  '%c'     ", c);
      else if( c == '\n')
      	printf("symbol:  '\\n'    ");
      else if( c == '\t')
      	printf("symbol:  '\\t'    ");
      else
        printf("symbol:  '%#hhx'  ", c);
      printf("frequency: %8zu  ", heap.array[0].syms[i].frequency);
      printf("codeword:   ");
      for( int z = heap.array[0].syms[i].bit; z < MAX_CODE; ++z)
        printf("%c", heap.array[0].syms[i].codeword[z]);
      printf("\n");
    }
    //determine the average VLC code length:
    double avgvlc = 0;
    for(size_t i = 0; i < heap.array[0].num_valid; ++i)
    {
      avgvlc += (MAX_CODE - heap.array[0].syms[i].bit - 1)*heap.array[0]
      .syms[i].frequency;
    }
    //avgvlc = avgvlc / heap.array[0].num_valid;
    avgvlc = avgvlc/ heap.array[0].frequency;
    
    //determine the fixed length code length:
    double flcl = 0;
    flcl = heap.array[0].num_valid;
    flcl = ceil(log2(flcl));
    
    printf("Average VLC code length:     %1.4f\n", avgvlc);
    printf("Fixed length code length:    %1.4f\n", flcl);


    return EXIT_SUCCESS;
}
