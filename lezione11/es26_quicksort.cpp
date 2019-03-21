/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
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
  bool
  preprocess( T a[], int N ) {
    int nG = 0;
    int nE = 0;
    int nL = 0;
    for ( int i = 1; i < N; ++i ) {
      T const & a0 = a[i-1];
      T const & a1 = a[i];
      if      ( a0 < a1 ) ++nG;
      else if ( a0 > a1 ) ++nL;
      else                ++nE;
    }
    bool ok = false;
    if ( nL == 0 ) {
      ok = true;
    } else if ( nG == 0 ) {
      std::reverse( a, a+N );
      ok = true;
    } else if ( nG < nL ) {
      std::reverse( a, a+N );
    }
    return ok;
  }

  static
  int
  median3( T const a[], int i0, int i1, int i2 ) {
    if ( a[i0] > a[i1] ) std::swap( i0, i1 );
    if ( a[i1] > a[i2] ) std::swap( i1, i2 );
    if ( a[i0] > a[i1] ) std::swap( i0, i1 );
    //if ( !(a[i0] <= a[i1] && a[i1] <= a[i2]) ) cerr << "FALLITO!";
    return i1;
  }

  static
  int
  median5( T const a[], int i0, int i1, int i2, int i3, int i4 ) {
    if ( a[i0] < a[i1] ) std::swap( i0, i1 );
    if ( a[i2] < a[i3] ) std::swap( i2, i3 );
    if ( a[i0] < a[i2] ) {
      std::swap( i0, i2 );
      std::swap( i1, i3 );
    }
    if ( a[i1] < a[i4] ) std::swap( i1, i4 );
    if ( a[i1] > a[i2] ) {
      if ( a[i2] > a[i4] ) return i2;
      return i4;
    } else {
      if ( a[i1] > a[i3] ) return i1;
      return i3;
    }
  }

  static
  int
  r_median( T a[], int lo, int hi ) {
    int m1, m2, m3;
    int N = hi-lo+1;
    if ( N > 10 ) {
      int eps2 = N>>2;
      int eps  = eps2>>1;
      m1 = r_median( a, lo,      lo+eps  );
      m2 = r_median( a, lo+eps2, hi-eps2 );
      m3 = r_median( a, hi-eps,  hi      );
    } else {
      m1 = lo;
      m2 = (lo+hi)>>1;
      m3 = hi;
    }
    return median3( a, m1, m2, m3 );
  }

  static
  int
  partition( T a[], int lo, int hi ) {
    int eps = (hi-lo)>>2;
    //int ipivot = Qsort<T>::median3( a, lo, (lo+hi)>>1, hi );
    int ipivot = Qsort<T>::median5( a, lo, lo+eps, lo+2*eps, hi-eps, hi );

    std::swap( a[lo], a[ipivot] );

    // salva pivot in posizione ilow
    ipivot  = lo;
    T pivot = a[ipivot];
    int i = lo;
    while ( ++i <= hi ) {
      if ( a[i] < pivot ) {
        // aggiunge a[i] alla lista elementi < pivot
        ++ipivot;
        std::swap( a[i], a[ipivot] );
        // gli elementi a[ilow+1..ipivot] < pivot
      }
    }
    // scambia a[ilow] <=> a[ipivot]
    // std::swap( a[ilow], a[ipivot] );
    a[lo]     = a[ipivot];
    a[ipivot] = pivot;
    return ipivot;
  }

  static
  int
  partition1( T a[], int LO, int hi ) {
    int eps = (hi-LO)>>2;
    //int ipivot = Qsort<T>::median3( a, LO, (LO+hi)>>1, hi );
    int ipivot = Qsort<T>::median5( a, LO, LO+eps, LO+2*eps, hi-eps, hi );
    std::swap( a[LO], a[ipivot] );
    T    pivot      = a[LO];
    int  lo         = LO+1;
    bool lo_less_hi = true;
    while ( lo_less_hi ) {
      while ( (lo_less_hi = lo <= hi) && a[hi] >= pivot ) --hi;
      while ( (lo_less_hi = lo <= hi) && a[lo] <= pivot ) ++lo;
      if ( lo_less_hi ) swap(a[lo], a[hi]);
    }
    swap(a[LO], a[hi]);
    return hi;
  }

  static
  void
  sort( T a[], int N ) {
    bool ok = preprocess( a, N );
    if ( ok ) return;

    std::vector<int> L, U;
    L.reserve(1000);
    U.reserve(1000);
    L.push_back(0);
    U.push_back(N-1);

    //int maxdeep = 0;
    while ( L.size() > 0 ) {
      //maxdeep = max(maxdeep, int(L.size()));
      int lo = L.back(); L.pop_back();
      int hi = U.back(); U.pop_back();
      int N  = hi-lo+1;

      if ( N > 80 ) {
        int ipivot = Qsort<T>::partition( a, lo, hi );
        L.push_back(lo);       U.push_back(ipivot-1);
        L.push_back(ipivot+1); U.push_back(hi);
      } else {
        Qsort<T>::insert_sort( a+lo, N );
      }
    }
    //cout << "maxdeep = " << maxdeep << '\n';
  }
};

static
void
check( int N, double v[], double v1[] ) {
  TicToc tm;

  tm.tic();
  Qsort<double>::sort(v,N);
  tm.toc();

  bool ok = check_if_sorted( v, N );
  if ( ok ) cout << "quicksort:Ordinamento corretto!\n";
  else      cout << "quicksort:Ordinamento fallito!\n";

  cout << "Elapsed (MIO) = " << tm.elapsed_ms() << "(ms)\n";

  tm.tic();
  sort(v1,v1+N); // ordinamento con STL
  tm.toc();
  cout << "Elapsed (STL) = " << tm.elapsed_ms() << "(ms)\n";

  double res = 0;
  for ( int i = 0; i < N; ++i )
    res += std::abs( v[i]-v1[i] );

  cout << "RES = " << res << '\n' ;
}


int
main() {
  int    N = 80000;
  double v[80000], v1[80000];

  Random rgen;
  TicToc tm;

  cout << "\nlog2(N) = " << log2(N) << "\n";

  cout << "\nRANDOM\n";
  for ( int i = 0; i < N; ++i )
    v1[i] = v[i] = rgen.dice( -10, 10 );

  check( N, v, v1 );

  cout << "\nORDERED\n";
  // vettore gia ordinato
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = i;
  check( N, v, v1 );

  cout << "\nREVERSED\n";
  // vettore rovescio
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = N-i;
  check( N, v, v1 );

  cout << "\nQUASI ORDERED\n";
  // vettore gia ordinato
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = i;
  for ( int i = 0; i < N; i += 10 )
    v1[i] = v[i] = rgen.dice( -10, 10 );
  check( N, v, v1 );

  cout << "\nQUASI REVERSED\n";
  // vettore rovescio
  for ( int i = 0; i < N; ++i ) v1[i] = v[i] = N-i;
  for ( int i = 0; i < N; i += 10 )
    v1[i] = v[i] = rgen.dice( -10, 10 );
  check( N, v, v1 );

  return 0;
};
