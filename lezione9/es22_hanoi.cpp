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
#include <iomanip> // per setw
#include <algorithm> // per std::swap

using namespace std;

/*\
  restituisce un vettore (vector<int>) con
  l'elenco  dei numeri primi <= N
\*/
void
hanoi(
  int        N,
  char const A[],
  char const B[],
  char const C[]
) {
  if ( N > 1 ) {
    hanoi( N-1, A, C, B );
    cout << A << " --> " << C << '\n';
    hanoi( N-1, B, A, C );
  } else {
    cout << A << " --> " << C << '\n';
  }
}

int
main( int argc, char * argv[] ) {
  if ( argc == 2 ) {
    int N;
    sscanf( argv[1], "%d", &N );
    TicToc tm;
    tm.tic();
    hanoi( N, "A", "B", "C" );
    tm.toc();
    cout << "\n\nElapsed (hanoi) = " << tm.elapsed_ms() << "(ms)\n";
  } else {
    cout << "Usage: " << argv[0] << " integer\n";
  }
  return 0;
};
