#include node_heap.h
#include <stdio.h>
#include <stdlib.h>

#static compareNode
#static sift_up
#static sift_down

int compareNode(Node n1, Node n2)
{
  return(n1.frequency - n2.frequency);
}

void sift_up( Heap * heap)
{
  int p = heap.size-1;
  while(p)
  {
    int parent = (p-1)/2;
    if(compareNode(heap.array[p],heap.array[parent])){
      break;
    }
    else
    {
      node temp = heap.array[p];
      heap.array[p] = heap.array[parent];
      heap.array[parent] = temp;
      
      p = parent
    }
  }
}

int sift_down( Heap * heap)
{
  int p = 0;
  while( (2*p) + 1 < size)
  {
    int lc = (2*p)+1;
    int rc = lc+1;
    int minc = lc;
    if(rc < size)
      if(compareNode(heap.array[lc], heap.array[rc]))
        minc = rc;
    if(compareNode(heap.array[minc],heap.array[p])){
      node temp = heap.array[p];
      heap.array[p] = heap.array[minc];
      heap.array[minc] = temp;
    }
  }
}

int read_symbols( size_t maxcount, Symbol syms[] )
{
  
}

void heap_init( Heap * heap )
{
  
  
}

void heap_make( Heap * heap, size_t length, Symbol symlist[] )
{
  for(int i = 0; i < length; ++i)
  {
    Node k;
    k.frequency = symlist[i].frequency;
    k.num_valid = 1;
    k.syms[0] = symlist[i];
    heap_add(heap, k);
  }
}

void heap_add( Heap * heap, Node node )
{
  if(heap.size < heap.capacity)
  {
    ++heap.size;
    heap.array[size-1] = node;
    sift_up(heap);
  }
}

Node heap_remove( Heap * heap )
{
  if(heap.size)
  {
    heap.array[0]=heap.array[size-1];
    --heap.size;
    sift_down(heap);
  }
}
