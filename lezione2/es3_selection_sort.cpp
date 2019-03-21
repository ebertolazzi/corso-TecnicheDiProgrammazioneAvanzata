/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
:|:
:|:
\*/

#include "course_lib.h"
#include <iostream>

using namespace std;

static
void
swap( double & a, double & b ) {
  double tmp = a; a = b; b = tmp;
}

/*\
:|: Cerca l'elemento massimo in un vettore di n elementi.
:|: Restituisce l'indice dell'elemento massimo.
\*/
static
int
find_max( double a[], int n ) {
  int ipos = 0;
  for ( int i = 1; i < n; ++i )
    if ( a[i] > a[ipos] )
      ipos = i;
  return ipos;
}

/*\
:|: Ordina il vettore a di n elementi per selezione.
:|: Si cerca il massimo di un vettore di n-elementi
:|: e si mette in coda.
:|: Poi di cerca il massimo di un vettore di (n-1)-elementi
:|: e si mette in coda e cosi via fino ad arrivare
:|: ad un vettore di 2 elementi.
\*/
static
void
select_sort( double a[], int n ) {
  int i = n;
  while ( i > 1 ) {
    int ipos = find_max( a, i );
    --i;
    swap( a[ipos], a[i] );
  }
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
  select_sort(v,N);
  tm.toc();

  bool ok = check_if_sorted( v, N );
  if ( ok ) cout << "Ordinamento corretto!\n";
  else      cout << "Ordinamento fallito!\n";

  cout << "Elapsed = " << tm.elapsed_ms() << "(ms)\n";

  return 0;
};
