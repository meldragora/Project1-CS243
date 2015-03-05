#include <node_heap.h>
#include <stdio.h>
#include <stdlib.h>

#static compareNode
#static sift_up
#static sift_down
#static contains

int compareNode(Node n1, Node n2)
{
  return(n1.frequency - n2.frequency);
}

void sift_up( Heap * heap)
{
  int p = heap->size-1;
  while(p)
  {
    int parent = (p-1)/2;
    if(compareNode(heap->array[p],heap->array[parent])){
      break;
    }
    else
    {
      node temp = heap->array[p];
      heap->array[p] = heap->array[parent];
      heap->array[parent] = temp;
      
      p = parent
    }
  }
}

int sift_down( Heap * heap)
{
  int p = 0;
  while( (2*p) + 1 < heap->size)
  {
    int lc = (2*p)+1;
    int rc = lc+1;
    int minc = lc;
    if(rc < size)
      if(compareNode(heap->array[lc], heap->array[rc]))
        minc = rc;
    if(compareNode(heap->array[minc],heap->array[p])){
      node temp = heap->array[p];
      heap->array[p] = heap->array[minc];
      heap->array[minc] = temp;
    }
  }
}

int contains( size_t maxcount, Symbol syms[], char c)
{
  for(int i = 0; i < maxcount; ++i)
  {
    if( syms[i].symbol == c)
      return i+1;
  }
  return 0;
}

///returns the number of unique symbols read.
int read_symbols( size_t maxcount, Symbol syms[] )
{
  int counter = 0;
  printf("Enter the message to be encoded:");
  do
  {
    char x = getchar;
    if(x == '\n')
      break;
    else if (!contains(maxcount, syms[], x))
    {
      Symbol s;
      s.frequency = 1;
      s.symbol = x;
      bit = MAX_CODE - 1;
      syms[counter] = s;
      ++counter;
    }
    else
    {
      ++syms[contains(maxcount, syms[], x)-1].frequency;
    }
  }while(true);
  return counter;
}

void heap_init( Heap * heap )
{
  heap->array[NSYMS];
  for( int i = 0; i < NSYMS; ++i)
  {
    heap->array[i] = {0,0, Symbol syms[NSYMS]};
  }
  heap->capacity = NSYMS;
  heap->size = 0;
}

///heap_make should be called after heap_init and read_symbols.
///the heap used for heap_init, the value returned by read_symbols,
///and the symlist used in read_symbols should be used.
void heap_make( Heap * heap, size_t length, Symbol symlist[] )
{
  if( !length > heap->capacity )
  {
    heap->size = length;
    for( int i = 0; i < length; ++i)
    {
      Node n;
      n.frequency = symlist[i].frequency;
      n.num_valid = 1;
      n.syms[NSYMS];
      heap_add( heap, n);
    }
  }
}

void heap_add( Heap * heap, Node node )
{
  if(heap->size < heap->capacity)
  {
    ++heap->size;
    heap->array[heap->size-1] = node;
    sift_up(heap);
  }
}

Node heap_remove( Heap * heap )
{
  Node n;
  if(heap->size)
  {
    heap->array[0]=heap->array[heap->size-1];
    --heap->size;
    sift_down(heap);
    n = heap->array[heap->size];
    heap->array[heap->size] = {0,0, Symbol syms[NSYMS]};
  }
  return n;
}
