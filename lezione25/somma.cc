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
#include <vector>
#include <limits>

using namespace std;

typedef int integer;

/*\
  Calcolo somma massima di interi in una successione
  con la regola che si possono aggiungere alla somma
  solo numeri >= dell'ultimo numero inserito.
\*/

static unsigned long Somma_count = 0;

integer
Somma(
  vector<integer> const & A, // lista dei numeri da sommare
  integer                 i, // somma nell'insione [A[i],A[i+1],...,]
  integer                 V  // solo numeri >= V
) {
  ++Somma_count; // contatore delle volte che Somma viene chiamata
  integer n = integer(A.size()); // quinti numeri?
  // base della ricorsione
  if ( i == n-1 ) {
    // caso triviale, un solo elemento da sommare
    if ( A[i] >= V ) return A[i];
    else             return 0;
  }

  // caso complesso, uso la ricorrenza
  if ( A[i] >= V ) {
    // posso inserire il numero
    // caso 1, provo ad inserire il numero
    integer res1 = A[i] + Somma( A, i+1, A[i] );
    // caso 2, NON inserisco il numero
    integer res2 = Somma( A, i+1, V );
    return std::max( res1, res2 );
  } else {
    // non posso inserire il numero
    return Somma( A, i+1, V );
  }
}

int
main() {

  Random rnd;

  integer         N = 150;
  vector<integer> A;

  A.clear();
  A.reserve(N);

  for ( integer i = 0; i < N; ++i )
    A.push_back( integer( rnd.dice( 0, 1000)) ) ;

  // cerco minimo possibile valore di un integer
  integer V = std::numeric_limits<integer>::min();

  integer S = Somma( A, 0, V );

  cout << "Lo Somma vale : " << S << "\n";
  cout << "Somma e' stata valuata " << Somma_count << " volte\n";
  return 0;
}
