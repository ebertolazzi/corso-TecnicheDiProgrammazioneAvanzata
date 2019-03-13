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
#include <iomanip>

using namespace std;

void
swap( double & a, double & b ) {
  double tmp = a; a = b; b = tmp;
}

/*\
:|:  ____        _     _     _        ____             _
:|: | __ ) _   _| |__ | |__ | | ___  / ___|  ___  _ __| |_
:|: |  _ \| | | | '_ \| '_ \| |/ _ \ \___ \ / _ \| '__| __|
:|: | |_) | |_| | |_) | |_) | |  __/  ___) | (_) | |  | |_
:|: |____/ \__,_|_.__/|_.__/|_|\___| |____/ \___/|_|   \__|
\*/

static
void
bubble_sort( double a[], int n ) {
  for ( int j = 1; j < n; ++j )
    for ( int i = 0; i < j; ++i )
      if ( a[i] > a[j] )
        swap( a[i], a[j] );
}

/*\
:|:  ___                     _     ____             _
:|: |_ _|_ __  ___  ___ _ __| |_  / ___|  ___  _ __| |_
:|:  | || '_ \/ __|/ _ \ '__| __| \___ \ / _ \| '__| __|
:|:  | || | | \__ \  __/ |  | |_   ___) | (_) | |  | |_
:|: |___|_| |_|___/\___|_|   \__| |____/ \___/|_|   \__|
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

static
void
insert_sort( double a[], int n ) {
  for ( int i = 1; i < n; ++i )
    insert( a, i );
}

/*\
:|:  ____       _           _   _               ____             _
:|: / ___|  ___| | ___  ___| |_(_) ___  _ __   / ___|  ___  _ __| |_
:|: \___ \ / _ \ |/ _ \/ __| __| |/ _ \| '_ \  \___ \ / _ \| '__| __|
:|:  ___) |  __/ |  __/ (__| |_| | (_) | | | |  ___) | (_) | |  | |_
:|: |____/ \___|_|\___|\___|\__|_|\___/|_| |_| |____/ \___/|_|   \__|
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

static
void
selection_sort( double a[], int n ) {
  int i = n;
  while ( i > 1 ) {
    int ipos = find_max( a, i );
    --i;
    swap( a[ipos], a[i] );
  }
}
/*\
:|:  ____  _          _ _   ____             _
:|: / ___|| |__   ___| | | / ___|  ___  _ __| |_
:|: \___ \| '_ \ / _ \ | | \___ \ / _ \| '__| __|
:|:  ___) | | | |  __/ | |  ___) | (_) | |  | |_
:|: |____/|_| |_|\___|_|_| |____/ \___/|_|   \__|
\*/

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
    for ( int k = 0; k < step; ++k )
      insert_sort( a+k, n-k, step );
    step = (step>>2)-1;
  }
  insert_sort( a, n, 1 );
}

static
void
check( double a[], int n, char const msg[] ) {
  bool ok = check_if_sorted( a, n );
  cout << msg << ":";
  if ( ok ) cout << "Ordinamento corretto!\n";
  else      cout << "Ordinamento fallito!\n";
}

int
main() {

  Random rgen;
  TicToc tm;

  int    n_ckeck = 0, NN[100];
  double tm_bubble[100], tm_insert[100], tm_selection[100], tm_shell[100];

  for( int N=100; N < 50000; N *= 2, ++n_ckeck ) {
    NN[n_ckeck] = N;
    cout << "N = " << N <<'\n';
    double *v, *a;
    AutoAllocate<double> mem1(N,&v);
    AutoAllocate<double> mem2(N,&a);
    for ( int i = 0; i < N; ++i )
      v[i] = rgen.dice( -10, 10 );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    bubble_sort(a,N);
    tm.toc();
    tm_bubble[n_ckeck] = tm.elapsed_ms();
    check( a, N, "Bubble Sort" );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    insert_sort(a,N);
    tm.toc();
    tm_insert[n_ckeck] = tm.elapsed_ms();
    check( a, N, "Insert Sort" );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    selection_sort(a,N);
    tm.toc();
    tm_selection[n_ckeck] = tm.elapsed_ms();
    check( a, N, "Selection Sort" );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    shell_sort(a,N);
    tm.toc();
    tm_shell[n_ckeck] = tm.elapsed_ms();
    check( a, N, "Shell Sort" );
  }

  /*\
  :|:  _____     _     _        _
  :|: |_   _|_ _| |__ | | ___  / |
  :|:   | |/ _` | '_ \| |/ _ \ | |
  :|:   | | (_| | |_) | |  __/ | |
  :|:   |_|\__,_|_.__/|_|\___| |_|
  \*/

  cout
    << "\n\n"
    << setw(6)  << "N"        << " "
    << setw(12) << "bubble"   << " "
    << setw(12) << "insert"   << " "
    << setw(12) << "selection"<< " "
    << setw(12) << "shell"    << " "
    << "\n----------------------------------------------------------\n";

  for ( int i = 0; i < n_ckeck; ++i )
    cout
      << setw(6)  << NN[i]           << " "
      << setw(12) << tm_bubble[i]    << " "
      << setw(12) << tm_insert[i]    << " "
      << setw(12) << tm_selection[i] << " "
      << setw(12) << tm_shell[i]     << "\n";

  cout
    << "----------------------------------------------------------\n"
    << setw(6)  << " "    << " "
    << setw(12) << "(ms)" << " "
    << setw(12) << "(ms)" << " "
    << setw(12) << "(ms)" << " "
    << setw(12) << "(ms)" << "\n\n\n";

  /*\
  |:|   _____     _     _        ____
  |:|  |_   _|_ _| |__ | | ___  |___ \
  |:|    | |/ _` | '_ \| |/ _ \   __) |
  |:|    | | (_| | |_) | |  __/  / __/
  |:|    |_|\__,_|_.__/|_|\___| |_____|
  \*/

  cout
    << setw(6)  << "N"        << " "
    << setw(12) << "bubble"   << " "
    << setw(12) << "insert"   << " "
    << setw(12) << "selection"<< " "
    << setw(12) << "shell"    << " "
    << "\n----------------------------------------------------------\n";

  for ( int i = 0; i < n_ckeck; ++i )
    cout
      << setw(6)  << NN[i]                         << " "
      << setw(12) << 1e6*tm_bubble[i]/(NN[i]*NN[i])    << " "
      << setw(12) << 1e6*tm_insert[i]/(NN[i]*NN[i])    << " "
      << setw(12) << 1e6*tm_selection[i]/(NN[i]*NN[i]) << " "
      << setw(12) << 1e6*tm_shell[i]/pow(NN[i],3./2.)  << "\n";

  cout
    << "----------------------------------------------------------\n"
    << setw(6)  << " "                << " "
    << setw(12) << "1e6*(ms)/N^2"     << " "
    << setw(12) << "1e6*(ms)/N^2"     << " "
    << setw(12) << "1e6*(ms)/N^2"     << " "
    << setw(12) << "1e6*(ms)/N^(3/2)" << "\n\n";

  return 0;
};
