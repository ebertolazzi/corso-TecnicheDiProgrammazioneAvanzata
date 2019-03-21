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

using std::setw;
using std::cout;

static
void
check( double a[], int n, char const msg[] ) {
  bool ok = check_if_sorted( a, n );
  cout << msg << ":";
  if ( ok ) cout << "Ordinamento corretto!\n";
  else      cout << "Ordinamento fallito!\n";
}

/*
template <>
bool
compare_gt( double const & a, double const & b )
{ return a > b; }
*/

int
main() {

  Random rgen;
  TicToc tm;

  typedef struct {
    int    N;
    double tm_bubble,
           tm_insert,
           tm_selection,
           tm_shell,
           tm_qsort,
           tm_msort;
  } time_table;

  int        n_ckeck = 0;
  time_table ttable[100];

  for( int N=80; N < 100000; N *= 2, ++n_ckeck ) {
    time_table * tt = &ttable[n_ckeck];
    tt->N = N;
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
    tt->tm_bubble = tm.elapsed_ms();
    check( a, N, "Bubble Sort" );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    insert_sort(a,N);
    tm.toc();
    tt->tm_insert = tm.elapsed_ms();
    check( a, N, "Insert Sort" );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    selection_sort(a,N);
    tm.toc();
    tt->tm_selection = tm.elapsed_ms();
    check( a, N, "Selection Sort" );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    shell_sort(a,N);
    tm.toc();
    tt->tm_shell = tm.elapsed_ms();
    check( a, N, "Shell Sort" );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    qsort(a,0,N-1);
    tm.toc();
    tt->tm_qsort = tm.elapsed_ms();
    check( a, N, "Quick Sort" );

    for ( int i = 0; i < N; ++i ) a[i] = v[i];
    tm.tic();
    mergesort(a,N);
    tm.toc();
    tt->tm_msort = tm.elapsed_ms();
    check( a, N, "Merge Sort" );

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
    << setw(12) << "qsort"    << " "
    << setw(12) << "msort"    << " "
    << "\n-----------------------------------------------------------------------\n";

  for ( int i = 0; i < n_ckeck; ++i )
    cout
      << setw(6)  << ttable[i].N            << " "
      << setw(12) << ttable[i].tm_bubble    << " "
      << setw(12) << ttable[i].tm_insert    << " "
      << setw(12) << ttable[i].tm_selection << " "
      << setw(12) << ttable[i].tm_shell     << " "
      << setw(12) << ttable[i].tm_qsort     << " "
      << setw(12) << ttable[i].tm_msort     << "\n";

  cout
    << "-----------------------------------------------------------------------\n"
    << setw(6)  << " "    << " "
    << setw(12) << "(ms)" << " "
    << setw(12) << "(ms)" << " "
    << setw(12) << "(ms)" << " "
    << setw(12) << "(ms)" << " "
    << setw(12) << "(ms)" << " "
    << setw(12) << "(ms)" << "\n\n\n";

  return 0;
};
