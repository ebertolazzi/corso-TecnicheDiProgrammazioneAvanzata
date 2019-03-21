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

template <typename T>
class Qsort {
public:

  static
  int
  median3( T const & a, T const & b, T const & c ) {
    if ( a <= b ) {
      if ( b <= c ) return 1; // b mediana a <= b <= c
      if ( a <= c ) return 2; // c mediana b < a <= c
      return 0; // a mediana c < a <= b
    } else {
      if ( a <= c ) return 0; // a mediana b < a <= c
      if ( b <= c ) return 2; // c mediana b <= c < a
      return 1; // b mediana c < b < a
    }
  }

  static
  int
  partition( T a[], int N ) {
    if ( N >= 3 ) {
      int imed = N>>1;
      switch ( Qsort<T>::median3( a[0], a[imed], a[N-1] ) ) {
      case 0:
        break;
      case 1:
        std::swap( a[0], a[imed] );
        break;
      case 2:
        std::swap( a[0], a[N-1] );
        break;
      }
    }
    // salva pivot in posizione ilow

    int ipivot = 0;
    T   pivot  = a[ipivot];
    int i = 0;
    while ( ++i < N ) {
      if ( a[i] < pivot ) {
        // aggiunge a[i] alla lista elementi < pivot
        ++ipivot;
        std::swap( a[i], a[ipivot] );
        // gli elementi a[ilow+1..ipivot] < pivot
      }
    }
    // scambia a[ilow] <=> a[ipivot]
    // std::swap( a[ilow], a[ipivot] );
    a[0   ]   = a[ipivot];
    a[ipivot] = pivot;
    return ipivot;
  }

  static
  void
  insert_sort( T a[], int N ) {
    for ( int n = 1; n < N; ++n ) {
      // a[0], a[1], ..., a[n-1] sono ordinati
      // inserisce a[n] nella posizione corretta.
      int i = n;
      for ( --i; i >= 0; --i ) {
        // continua a inserire se non soddisfa l'ordinamento
        if ( a[i] <= a[i+1] ) break;
        std::swap( a[i], a[i+1] );
      }
    }
  }
  static
  void
  sort( T a[], int N ) {
    if ( N > 50 ) {
      int ipivot = Qsort<T>::partition( a, N );
      Qsort<T>::sort( a, ipivot );
      Qsort<T>::sort( a+ipivot+1, N-ipivot-1 );
    } else {
      Qsort<T>::insert_sort( a, N );
    }
  }
};

void
ordina( int vec[], int N ) {
  Qsort<int>::sort( vec, N );
}
