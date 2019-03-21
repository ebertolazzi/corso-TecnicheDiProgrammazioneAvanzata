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
#include <algorithm> // per std::swap

using namespace std;

/*\
:|: Ordinamento quicksort, vedi note online
:|: per la descrizione
\*/

/*\
  divide il vettore a[ilow..ihigh] in due sottovettori dove
  tutti gli elementi a sinistra di ipivot
  (compreso l’elemento in posizione ipivot)
  sono minori o uguali tutti gli elementi
  a destra di ipivot
\*/
static
int
partition1( double a[], int ilow, int ihigh ) {
  double pivot      = a[ilow];
  int    lo         = ilow+1;
  int    hi         = ihigh;
  bool   lo_less_hi = lo < hi;
  while ( lo_less_hi ) {
    while ( (lo_less_hi = lo < hi) && a[hi] >= pivot ) --hi;
    while ( (lo_less_hi = lo < hi) && a[lo]  < pivot ) ++lo;
    // dopo i 2 loop
    // a[hi+1..ihigh] >= pivot && a[hi] < pivot
    // a[ilow+1..lo-1] < pivot && a[lo] >= pivot
    if ( lo_less_hi ) swap(a[lo], a[hi]);
  }
  /*
  // alla fine del loop lo == hi
  // caso 1: pivot è minimo stretto, allora
  //   a[lo] > pivot e la partizione è
  //   [ilow,ilow] [ilow+1,ihigh]
  */
  if ( a[lo] > pivot ) return ilow;
  /*
  // caso 2: pivot non è minimo, allora
  //   a[low+1..lo] < a[ilow] && a[lo+1..ihigh] >= a[ilow]
  //   posso scambiare a[low] con a[lo] ed ottenere
  //   a[low..lo-1] <= a[lo] && a[lo+1..ihigh] >= a[lo]
  */
  a[ilow] = a[lo]; // swap (a[ilow], a[lo]);
  a[lo]   = pivot; // sfrutto pivot == a[ilow]
  return lo;
}

static
int
partition2( double a[], int ilow, int ihigh ) {
  int    ipivot = ilow;
  double pivot  = a[ilow]; // salva pivot in posizione ilow
  int i = ilow;
  while ( ++i <= ihigh ) {
    if ( a[i] < pivot ) {
      // aggiunge a[i] alla lista elementi < pivot
      ++ipivot;
      std::swap( a[i], a[ipivot] );
      // gli elementi a[ilow+1..ipivot] < pivot
    }
  }
  // scambia a[ilow] <=> a[ipivot]
  // std::swap( a[ilow], a[ipivot] );
  a[ilow]   = a[ipivot];
  a[ipivot] = pivot;
  return ipivot;
}

static
void
quicksort( double a[], int ilow, int ihigh ) {
  if ( ilow < ihigh ) {
    int ipivot = partition1( a, ilow, ihigh );
    //int ipivot = partition2( a, ilow, ihigh );
    quicksort( a, ilow, ipivot-1 );
    quicksort( a, ipivot+1, ihigh );
  }
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
  quicksort(v,0,N-1);
  tm.toc();

  bool ok = check_if_sorted( v, N );
  if ( ok ) cout << "quicksort:Ordinamento corretto!\n";
  else      cout << "quicksort:Ordinamento fallito!\n";

  cout << "Elapsed = " << tm.elapsed_ms() << "(ms)\n";

  tm.tic();
  sort(v1,v1+N); // ordinamento con STL
  tm.toc();
  cout << "Elapsed (STL) = " << tm.elapsed_ms() << "(ms)\n";

  // vettore gia ordinato
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = i;

  tm.tic();
  quicksort(v,0,N-1);
  tm.toc();

  ok = check_if_sorted( v, N );
  if ( ok ) cout << "quicksort:Ordinamento corretto!\n";
  else      cout << "quicksort:Ordinamento fallito!\n";

  cout << "Elapsed (ordered) = " << tm.elapsed_ms() << "(ms)\n";

  tm.tic();
  sort(v1,v1+N); // ordinamento con STL
  tm.toc();
  cout << "Elapsed (STL) = " << tm.elapsed_ms() << "(ms)\n";

  // vettore rovescio
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = N-i;

  tm.tic();
  quicksort(v,0,N-1);
  tm.toc();

  ok = check_if_sorted( v, N );
  if ( ok ) cout << "quicksort:Ordinamento corretto!\n";
  else      cout << "quicksort:Ordinamento fallito!\n";

  cout << "Elapsed (rovescio) = " << tm.elapsed_ms() << "(ms)\n";

  tm.tic();
  sort(v1,v1+N); // ordinamento con STL
  tm.toc();
  cout << "Elapsed (STL) = " << tm.elapsed_ms() << "(ms)\n";

  return 0;
};
