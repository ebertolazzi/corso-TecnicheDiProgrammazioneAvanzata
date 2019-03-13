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

using namespace std;

/*\
:|: Ordinamento mergesort, vedi note online
:|: per la descrizione
\*/

static
void
merge( double a1[], int n1,
       double a2[], int n2,
       double out[] ) {
  int i1 = 0;
  int i2 = 0;
  int i  = 0;
  while( i1 < n1 && i2 < n2 ) {
    if ( a1[i1] < a2[i2] ) { out[i] = a1[i1]; ++i1; }
    else                   { out[i] = a2[i2]; ++i2; }
    ++i;
  }
  while ( i1 < n1 ) out[i++] = a1[i1++];
  while ( i2 < n2 ) out[i++] = a2[i2++];
}

static
void
mergesort( double a[], int n ) {
  /* Base case: 0- or 1-element lists are already sorted. */
  if ( n <= 1 ) return;

  /* Split v into two subvectors. */
  int n2 = n>>1; // n/2
  vector<double> left(n2), right(n-n2);
  for ( int i = 0; i < n2;   ++i ) left[i]  = a[i];
  for ( int i = 0; i < n-n2; ++i ) right[i] = a[n2+i];

  /* Recursively sort these arrays. */
  mergesort( &left.front(),  n2 );
  mergesort( &right.front(), n-n2 );

  /* Combine them together. */
  merge( &left.front(), n2, &right.front(), n-n2, a);
}

int
main() {
  int N = 1000000;
  vector<double> v(N), v1;
  v1.resize(N);

  Random rgen;
  TicToc tm;
  for ( int i = 0; i < N; ++i )
    v1[i] = v[i] = rgen.dice( -10, 10 );

  tm.tic();
  mergesort(&v.front(),N);
  tm.toc();

  bool ok = check_if_sorted( &v.front(), N );
  if ( ok ) cout << "mergesort:Ordinamento corretto!\n";
  else      cout << "mergesort:Ordinamento fallito!\n";

  cout << "Elapsed = " << tm.elapsed_ms() << "(ms)\n";

  // vettore gia ordinato
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = i;

  tm.tic();
  mergesort(&v.front(),N);
  tm.toc();

  // v.front()  = primo elemento del vettore
  // &v.front() = indirizzo primo elemento del vettore
  ok = check_if_sorted( &v.front(), N );
  if ( ok ) cout << "mergesort:Ordinamento corretto!\n";
  else      cout << "mergesort:Ordinamento fallito!\n";

  cout << "Elapsed (ordered) = " << tm.elapsed_ms() << "(ms)\n";

  // vettore rovescio
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = N-i;

  tm.tic();
  mergesort( &v.front(), N );
  tm.toc();

  ok = check_if_sorted( &v.front(), N );
  if ( ok ) cout << "mergesort:Ordinamento corretto!\n";
  else      cout << "mergesort:Ordinamento fallito!\n";

  cout << "Elapsed (rovescio) = " << tm.elapsed_ms() << "(ms)\n";

  return 0;
};
