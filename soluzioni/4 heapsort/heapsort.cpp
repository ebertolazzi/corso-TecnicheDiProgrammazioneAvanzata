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

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "course_lib.h"

using namespace std;

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
static
void
heapify( int arr[], int n, int i) {
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

int
main(void) {

  ifstream fin("input.txt");
  ofstream fout("output.txt");

  int n;
  fin >> n;
  int * vec;
  AutoAllocate<int> A1( n, &vec );
  for ( int i=0; i<n; ++i ) fin >> vec[i];
  fin.close();

  // Build heap (rearrange array)
  for ( int i = n / 2 - 1; i >= 0; --i )
    heapify( vec, n, i );

  fout << n << '\n';
  for ( int i=0; i<n; ++i ) fout << vec[i] << " ";
  fout << '\n';

  // One by one extract an element from heap
  for ( int i=n-1; i>=0; --i ) {
    // Move current root to end
    std::swap(vec[0], vec[i]);

    // call max heapify on the reduced heap
    heapify( vec, i, 0 );
  }

  for ( int i=0; i<n; ++i ) fout << vec[i] << " ";
  fout << '\n';

  fout.close();
  return 0;
}
