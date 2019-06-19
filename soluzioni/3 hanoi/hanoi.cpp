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

#include <fstream>
#include <vector>

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
