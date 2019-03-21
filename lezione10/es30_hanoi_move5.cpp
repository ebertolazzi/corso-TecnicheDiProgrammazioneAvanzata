/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
:|:
\*/

#include "hanoi_lib5.h"
#include <vector>
#include <stdio.h>

using namespace std;

void
hanoi(
  int N,
  int A,
  int B,
  int C,
  vector<int> & from,
  vector<int> & to
) {
  if ( N > 1 ) {
    hanoi( N-1, A, C, B, from, to );
    from.push_back(A);
    to.push_back(C);
    hanoi( N-1, B, A, C, from, to );
  } else {
    from.push_back(A);
    to.push_back(C);
  }
}

void
hanoi(
  int           N,
  vector<int> & from,
  vector<int> & to
) {
  from.clear(); from.reserve(10000);
  to.clear();   to.reserve(10000);
  hanoi( N, 1, 2, 3, from, to );
}

int
main( int narg, char const * argv[] ) {

  if ( narg != 2 ) {
    cerr << "usage: " << argv[0] << " N (integer)\n";
    exit(0);
  }
  int N;
  sscanf( argv[1], "%d", &N );
  Hanoi_status HS(N);
  HS.check();

  //HS.init( N );

  vector<int> from, to;
  int dm;
  hanoi( N, from, to );

  HS.plot();

  // HS.N = 10; non posso cambiare dato protetto

  bool ok = true;
  for ( int ns = 0; ok && ns < int(from.size()); ++ns ) {
    ok = HS.move( from[ns], to[ns], dm );
    HS.plot();
    cout
      << "[" << ns << "] moved disk " << dm
      << " from " << from[ns]
      << " to " << to[ns]
      << "\n\n";
  }
  return 0;
}
