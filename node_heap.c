#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "node_heap.h"

///@author Tyler Quesnel

static int compareNode(Node n1, Node n2)
{
  return(n1.frequency - n2.frequency);
}

static void sift_up( Heap * heap)
{
  int p = heap->size-1;
  while(p > 0)
  {
    int parent = (p-1)/2;
    if(compareNode(heap->array[p],heap->array[parent]) > 0){
      break;
    }
    else
    {
      Node temp = heap->array[p];
      heap->array[p] = heap->array[parent];
      heap->array[parent] = temp;
      
      p = parent;
    }
  }
}

static void sift_down( Heap * heap)
{
  size_t p = 0;
  while( (2*p) + 1 < heap->size)
  {
    size_t lc = (2*p)+1;
    size_t rc = lc+1;
    size_t minc = lc;
    if(rc < heap->size)
      if(compareNode(heap->array[lc], heap->array[rc]) > 0)
        minc = rc;
    if(compareNode(heap->array[p],heap->array[minc])){
      Node temp = heap->array[p];
      heap->array[p] = heap->array[minc];
      heap->array[minc] = temp;
      p = minc;
    }
    else
      break;
  }
  
}

static size_t contains( size_t maxcount, Symbol syms[], char c)
{
  for(size_t i = 0; i < maxcount; ++i)
  {
    if( syms[i].symbol == c)
      return i+1;
  }
  return 0;
}

///returns the number of unique symbols read.  Case sensitive.
int read_symbols( size_t maxcount, Symbol syms[] )
{
  int counter = 0;
  printf("Enter the message to be encoded then hit CTRL-D:\n");
  char p;
  while((p = getchar()) != EOF){
    if(p == NUL)
    {
      break;
    }
    else if (!contains(maxcount, syms, p))
    {
      Symbol s;
      s.frequency = 1;
      s.symbol = p;
      s.bit = MAX_CODE - 1;
      syms[counter] = s;
      ++counter;
    }
    else
    {
      ++syms[contains(maxcount, syms, p)-1].frequency;
    }
  }
  return counter;
}

void heap_init( Heap * heap )
{
  heap->capacity = NSYMS;
  heap->size = 0;
  
}

///heap_make should be called after heap_init and read_symbols.
///the heap used for heap_init, the value returned by read_symbols,
///and the symlist used in read_symbols should be used.
void heap_make( Heap * heap, size_t length, Symbol symlist[] )
{
  if( length <= heap->capacity )
  {
    for( size_t i = 0; i < length; ++i)
    {
      Node n;
      n.frequency = symlist[i].frequency;
      n.num_valid = 1;
      n.syms[0] = symlist[i];
      heap_add( heap, n);
    }
  }
  //for(size_t x = 0; x < heap->size; ++x)
    //printf("%c\n", heap->array[x].syms[0].symbol);
}

void heap_add( Heap * heap, Node node )
{
  if(heap->size < heap->capacity)
  {
    ++heap->size;
    heap->array[heap->size-1] = node;
    sift_up(heap);
  }
  /*These print statements were used to help me check for errors.
  printf("%zu", heap->size);
  for(size_t i = 0; i < heap->size; ++i)
  {
    printf("frequency: %zu\n", heap->array[i].frequency);
  }
  printf("\n");*/
}

Node heap_remove( Heap * heap )
{
  Node n;
  if(heap->size)
  {
    n = heap->array[0];
    heap->array[0]=heap->array[heap->size-1];
    --heap->size;
    sift_down(heap);
    heap->array[heap->size].frequency = 0;
	Node blank;
	heap->array[heap->size] = blank;
    heap->array[heap->size].num_valid = 0;
  }
  return n;
}
