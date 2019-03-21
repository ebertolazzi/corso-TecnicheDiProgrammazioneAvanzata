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

using namespace std;

int
bsearch( int A[], int L, int U, int V ) {
  if ( L == U ) {
    // vettore comn 1 solo elemento
    if ( V <= A[L] ) return L;
    // if ( V == A[L] ) return L;
    // if ( V <  A[L] ) return L;
    return L+1;
  } else {
    int M = (L+U)>>1; // (L+M)/2 e tronco a intero
    if ( A[M] == V ) return M; // trovato
    if ( V < A[M] ) return bsearch( A, L, std::max(L,M-1), V );
    return bsearch( A, std::min(U,M+1), U, V );
  }
}

/*\

  compitino 1
  fare bsearch NON ricorsiva

  compitino 2
  ordinare vettore usando bsearch
  misurare tempi e confrontarsi con algo precedenti.

  compitino 3
  leggere upper_bound di STL e provare a usarlo

\*/




int
main() {
  int N = 10;
  int A[] = { 1, 2, 5, 13, 45, 123, 200, 300, 301, 302 };

  int r13 = bsearch( A, 0, N-1, 13 );
  cout << "search 13 = " << r13 << '\n';

  int r123 = bsearch( A, 0, N-1, 123 );
  cout << "search 123 = " << r123 << '\n';

  int r299 = bsearch( A, 0, N-1, 299 );
  cout << "search 299 = " << r299 << '\n';

  return 0;
};
