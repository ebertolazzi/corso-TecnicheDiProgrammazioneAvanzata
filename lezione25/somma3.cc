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

integer const N    = 100000;
integer const Nmax = 1000;
integer table[N][Nmax+1];

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
    integer res = A[i] >= V ? A[i] : 0;
    if ( V >= 0 ) table[i][V] = res;
    return res;
  }

  // controllo se la funzione è gia stata calcolata
  // (interrompo ricorsione)

  integer res;
  if ( V >= 0 ) {
    res = table[i][V];
    if ( res >= 0 ) {
      // valore trovato
      return res;
    }
  }

  // caso complesso, uso la ricorrenza e memorizzo il valore calcolato
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
  if ( V >= 0 ) table[i][V] = res;
  return res;
}

int
main() {

  Random rnd;

  vector<integer> A;

  A.clear();
  A.reserve(N);

  for ( integer i = 0; i < N; ++i )
    A.push_back( integer( rnd.dice( 0, Nmax)) ) ;

  // inizializzo la tabella di memo(r)izzazione
  /*
    table[0] = indirizzo inizio tabella in memoria
    table[N] = indirizzo (ultima riga + 1), cioe'  primo numero
               fuori dalla tabella. "Past to the last"

  */
  std::fill( table[0], table[N], -1 );

  // cerco minimo possibile valore di un integer
  integer V = std::numeric_limits<integer>::min();

  integer S = Somma( A, 0, V );

  cout << "Lo Somma vale : " << S << "\n";
  cout << "Somma e' stata valuata " << Somma_count << " volte\n";
  cout << "La tabella di memorizzazione usa " << N*(Nmax+1) << " elementi\n";
  return 0;
}
