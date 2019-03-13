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

using namespace std;

/*\
:|: Ordinamento shell sort, vedi note online
:|: per la descrizione
\*/

static
void
swap( double & a, double & b ) {
  double tmp = a; a = b; b = tmp;
}

static
void
insert( double a[], int n,int step ) {
  int i = n;
  for ( i -= step; i >= 0; i -= step )
    if ( a[i] > a[i+step] )
      swap( a[i], a[i+step] );
    else
      break;
}

static
void
insert_sort( double a[], int n, int step ) {
  for ( int i = step; i < n; i += step )
    insert( a, i, step );
}

static
void
shell_sort( double a[], int n ) {
  int step = n>>3;
  while ( step > 0 ) {
    cout << "step = " << step << '\n';
    for ( int k = 0; k < step; ++k )
      insert_sort( a+k, n-k, step );
    step = (step>>2)-1;
  }
  insert_sort( a, n, 1 );
}

int
main() {
  int    N = 10000;
  double v[10000];
  Random rgen;
  TicToc tm;
  for ( int i = 0; i < N; ++i )
    v[i] = rgen.dice( -10, 10 );

  tm.tic();
  shell_sort(v,N);
  tm.toc();

  bool ok = check_if_sorted( v, N );
  if ( ok ) cout << "Ordinamento corretto!\n";
  else      cout << "Ordinamento fallito!\n";

  cout << "Elapsed = " << tm.elapsed_ms() << "(ms)\n";

  return 0;
};
