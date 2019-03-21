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
:|: Dato un vettore `a` di n+1 elementi
:|: con a[0], a[1], ..., a[n-1] ordinati
:|: inserisce a[n] nella posizione corretta.
\*/
static
void
insert( double a[], int n ) {
  int i = n;
  for ( --i; i >= 0; --i )
    if ( a[i] > a[i+1] )
      swap( a[i], a[i+1] );
    else
      break;
}

/*\
:|: Ordina il vettore usanfo l'algoritmo
:|: di inserzione.
:|: costruisce i vettori si lunghezza 1,2,..,n
:|: ordinati inserendo un elemento alla volta
:|: nei vettori gia ordinati.
\*/
void
insert_sort( double a[], int n ) {
  for ( int i = 1; i < n; ++i )
    insert( a, i );
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
  insert_sort(v,N);
  tm.toc();

  bool ok = check_if_sorted( v, N );
  if ( ok ) cout << "Ordinamento corretto!\n";
  else      cout << "Ordinamento fallito!\n";

  cout << "Insert Sort: Elapsed = " << tm.elapsed_ms() << "(ms)\n";

  return 0;
};
