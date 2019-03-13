/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi e prof. Andrea Del Prete
:|:
:|:
\*/

#include "course_lib.h"
#include <iostream>
#include <algorithm> // per std::swap

#include <string.h> // per prototipo strcmp

using namespace std;

/*\
:|: Ordinamento heapsort, vedi note online
:|: per la descrizione
\*/

// C++ program for implementation of Heap Sort
#include <iostream>

using namespace std;

void
insert_into_heap( double arr[], int ipos ) {
  while ( ipos > 0 ) {
    int father = (ipos-1)>>1;
    if ( arr[father] >= arr[ipos] ) break;
    std::swap( arr[father], arr[ipos] );
    ipos = father;
  }
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void
heapify( double arr[], int n, int i) {
  while ( true ) {
    int largest = i;       // Initialize largest as root
    int l       = 2*i + 1; // left  = 2*i + 1
    int r       = l+1;     // right = 2*i + 2

    // If left child is larger than root
    if ( l < n && arr[l] > arr[largest] ) largest = l;

    // If right child is larger than largest so far
    if ( r < n && arr[r] > arr[largest] ) largest = r;

    // If largest is not root
    if ( largest == i ) break;
    std::swap( arr[i], arr[largest] );
    // Recursively heapify the affected sub-tree
    i = largest;
  }
}

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void
heapify2( double arr[], int n, int i) {
  int largest = i;       // Initialize largest as root
  int l       = 2*i + 1; // left  = 2*i + 1
  int r       = l+1;     // right = 2*i + 2

  // If left child is larger than root
  if ( l < n && arr[l] > arr[largest] ) largest = l;

  // If right child is larger than largest so far
  if ( r < n && arr[r] > arr[largest] ) largest = r;

  // If largest is not root
  if ( largest != i ) {
    std::swap( arr[i], arr[largest] );
    // Recursively heapify the affected sub-tree
    heapify( arr, n, largest );
  }
}

// main function to do heap sort
void
heapSort( double arr[], int n) {
  // Build heap (rearrange array)
  for ( int i = n / 2 - 1; i >= 0; --i )
    heapify( arr, n, i );

  //for ( int ipos = 1; ipos < n ; ++ipos )
  //  insert_into_heap( arr, ipos );

  // One by one extract an element from heap
  for ( int i=n-1; i>=0; --i ) {
    // Move current root to end
    std::swap(arr[0], arr[i]);

    // call max heapify on the reduced heap
    heapify( arr, i, 0 );
  }
}

void
check( double const v[], int N ) {
  bool ok = check_if_sorted( v, N );
  if ( ok ) {
    TermColor::set_COLOR_GREEN();
    cout << "heapsort:Ordinamento corretto!\n";
  } else {
    TermColor::set_COLOR_RED();
    cout << "heapsort:Ordinamento fallito!\n";
  }
  TermColor::set_COLOR_DEFAULT();
}

int
main() {
  int    N = 80000;
  double v[80000], v1[80000];
  Random rgen;
  TicToc tm;
  for ( int i = 0; i < N; ++i )
    v1[i] = v[i] = rgen.dice( -10, 10 );

  tm.tic();
  heapSort(v,N);
  tm.toc();

  check( v, N );

  cout << "Elapsed = " << tm.elapsed_ms() << "(ms)\n";

  tm.tic();
  sort(v1,v1+N); // ordinamento con STL
  tm.toc();
  cout << "Elapsed (STL) = " << tm.elapsed_ms() << "(ms)\n";

  // vettore gia ordinato
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = i;

  tm.tic();
  heapSort(v,N);
  tm.toc();

  check( v, N );

  cout << "Elapsed (ordered) = " << tm.elapsed_ms() << "(ms)\n";

  tm.tic();
  sort(v1,v1+N); // ordinamento con STL
  tm.toc();
  cout << "Elapsed (STL) = " << tm.elapsed_ms() << "(ms)\n";

  // vettore rovescio
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = N-i;

  tm.tic();
  heapSort(v,N);
  tm.toc();

  check( v, N );

  cout << "Elapsed (rovescio) = " << tm.elapsed_ms() << "(ms)\n";

  tm.tic();
  sort(v1,v1+N); // ordinamento con STL
  tm.toc();
  cout << "Elapsed (STL) = " << tm.elapsed_ms() << "(ms)\n";

  return 0;
};
