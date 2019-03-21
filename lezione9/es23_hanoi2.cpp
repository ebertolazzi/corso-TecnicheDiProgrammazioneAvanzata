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
#include <iomanip> // per setw
#include <algorithm> // per std::swap

using namespace std;

string
disk( int N, int d ) {
  string res = "";
  for ( int i = N-d; i > 0; --i ) res += " ";
  for ( int i = 0;   i < d; ++i ) res += "o";
  res += "|" ;
  for ( int i = 0;   i < d; ++i ) res += "o";
  for ( int i = N-d; i > 0; --i ) res += " ";
  return res;
}

string
base( int N ) {
  string res = "";
  for ( int i = 2*N+1; i > 0; --i ) res += "=";
  return res;
}

void
hanoi_plot(
  int N,
  int A[],
  int B[],
  int C[]
) {
  for ( int i = N-1; i >= 0; --i ) {
    cout
      << disk( N, A[i] )
      << disk( N, B[i] )
      << disk( N, C[i] )
      << '\n';
  }
  cout << base(N) << base(N) << base(N) << '\n';
}

int
main( int argc, char * argv[] ) {
  int N = 10;
  int A[N], B[N], C[N];
  std::fill( A, A+N, 0);
  std::fill( B, B+N, 0);
  std::fill( C, C+N, 0);
  A[0] = 1;
  A[1] = 2;
  A[5] = 4;
  C[0] = 3;
  hanoi_plot( N, A, B, C );
  return 0;
};
