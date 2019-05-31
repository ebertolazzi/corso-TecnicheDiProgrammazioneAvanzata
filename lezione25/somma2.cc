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
#include <map>
#include <limits>

using namespace std;

typedef int integer;

/*\
  Calcolo somma massima di interi in una successione
  con la regola che si possono aggiungere alla somma
  solo numeri >= dell'ultimo numero inserito.
\*/

static unsigned long Somma_count = 0;

/*\
  Memorizzo i risultati gia calcolati in una mappa
  RES = Somma( A, i, V )
  chiave -> pair<i,V>
  valore -> RES
\*/

// faccio degli alias per migliorare lettura dei tipi
typedef std::pair<integer,integer>     CoppiaIndici;
typedef std::map<CoppiaIndici,integer> CoppiaIndici_a_valore;

static CoppiaIndici_a_valore Somma_stored;

integer
Somma(
  vector<integer> const & A, // lista dei numeri da sommare
  integer                 i, // somma nell'insione [A[i],A[i+1],...,]
  integer                 V  // solo numeri >= V
) {
  std::pair<integer,integer> IDX(i,V); // IDX coppia di numeri

  ++Somma_count; // contatore delle volte che Somma viene chiamata
  integer n = integer(A.size()); // quinti numeri?
  // base della ricorsione
  if ( i == n-1 ) {
    // caso triviale, un solo elemento da sommare
    integer res = A[i] >= V ? A[i] : 0;
    Somma_stored[IDX] = res;
    return res;
  }

  // controllo se la funzione è gia stata calcolata
  // (interrompo ricorsione)

  // cerco IDX nella mappa
  CoppiaIndici_a_valore::iterator it = Somma_stored.find( IDX );

  if ( it != Somma_stored.end() ) {
    // valore trovato
    // it->first   chiave (coppia di interi)
    // it->second  valore
    return it->second;
  }

  // caso complesso, uso la ricorrenza e memorizzo il valore calcolato
  integer res;
  if ( A[i] >= V ) {
    // posso inserire il numero
    // caso 1, provo ad inserire il numero
    integer res1 = A[i] + Somma( A, i+1, A[i] );
    // caso 2, NON inserisco il numero
    integer res2 = Somma( A, i+1, V );
    res = std::max( res1, res2 );
  } else {
    // non posso inserire il numero
    res = Somma( A, i+1, V );
  }
  Somma_stored[IDX] = res;
  return res;
}

int
main() {

  Random rnd;

  integer         N = 10000;
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
  cout << "La tabella di memorizzazione usa " << Somma_stored.size() << " elementi\n";
  return 0;
}
