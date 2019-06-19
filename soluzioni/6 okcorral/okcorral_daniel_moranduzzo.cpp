#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "course_lib.h"

using namespace std;

//implemento insertion sort
template <typename T>
void
insertsort(T vec[], int first, int last){

  for ( int i = first + 1; i <= last; i++)
  {
    int key = vec[i];
    int j = i - 1;

    while (j >= first && vec[j] > key)
    {
      vec[j+1] = vec[j];
      j = j - 1;
    }
    vec[j+1] = key;
  }
  return;
}

//implemento heapsort
template <typename T>
void 
  heapify(T vec[], int i, int first, int last) {
    
    int max = i ; // inizializzo max come nodo radice i
    int l = 2*(i - first) + 1 + first; //figlio sinistro
    int r = l + 1; // figlio destro
    
    // se il figlio sinistro è maggiore della radice
    if (l <= last && vec[l] > vec[max])
       max = l;

    // se il figlio destro è maggiore della radice
    if (r <= last && vec[r] > vec[max])
      max = r;

    //se max non è più la radice scambio valori di max e i
    if (max != i) {
      swap(vec[i], vec[max]); // scambio max e i
      heapify(vec, max, first, last); // richiamo ricorsivamente
    }
  }

template <typename T>
void
heapsort(T vec[], int first, int last) {
  // build heap
  for(int i = (last + first -1)/2; i >= first; i--)
  {
    heapify(vec,i, first, last);
  }   
  for(int i = last; i >= first ; i--)
  {
    swap(vec[first],vec[i]);
    heapify(vec, first, first, i - 1);
  }
}

// implemento quicksort
template <typename T>
static
int
part(T vec[], int low, int high) {
  
  int pivot = vec[high]; 
  
  int lo = (low - 1); // indici dell'elemento + piccolo

  for (int i = low; i <= (high - 1); i++)
  {
    if (vec[i] <= pivot)
    {
      lo++;
      swap(vec[lo],vec[i]);
    }
  }
  
  swap(vec[lo+1],vec[high]);
  return (lo + 1);      
}


// implemento introsort
template <typename T>
void
introsort(T vec[], int first, int last, int maxdepth) {
  int size = (last-first + 1);
  if (size < 20)
    insertsort( vec , first, last);
  //else if (maxdepth == 0) {
   // heapsort(vec, first, last);
  //}
  else 
  {
    int ipivot = part(vec, first, last);
    introsort(vec, first, ipivot - 1, maxdepth - 1);
    introsort(vec, ipivot + 1, last, maxdepth - 1);
  }
}


void
ordina( int vec[], int N ) {
  int maxdepth = 2*log(N);
  introsort(vec, 0, N-1, maxdepth);
}