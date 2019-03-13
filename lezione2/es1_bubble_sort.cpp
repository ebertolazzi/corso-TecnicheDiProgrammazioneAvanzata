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

using namespace std; // per evitare di scrivere std::cout

/*\
:|:  funzione che scambia il contenuto gli argomenti a e b
:|:
:|:  & = passare argomento per "riferimento"
\*/

void // funzione che non restituisce niente == subroutine
swap( double & a, double & b ) {
  double tmp = a; a = b; b = tmp;
}

/*\

  A = istruzione eseguita 1 volta a inizio ciclo
  B = expressione booleana eseguita all'inizio di ogni ciclo
      vera  -> il ciclo viene eseguito
      false -> esce dal ciclo for
  C = istruzione eseguita alla fine di ogni ciclo
  D = istruzione eseguita per ogni ciclo

  for ( A ; B ; C ) D;

  PSEUDO CODICE

  A;

loop:

  if ( B ) {
    C ;
    D ;
    goto loop;
  }

  double a[] ==> l'argomento è un vettore C di dimensione non specificata
  int n      ==> l'argomento è la dimensione del vettore da ordinare


  a = indirizzo dove si trova il blocco di memoria del vettore `a`
  +--+--+--+--+--+--+--+ ..... +--+--+--+
  |  |  |  |  |  |  |  |       |  |  |  |  vettore a
  +--+--+--+--+--+--+--+ ..... +--+--+--+

\*/

void
bubble_sort( double a[], int n ) {
  for ( int i = 0; i < n-1; ++i )
    for ( int j = i+1; j < n; ++j )
      if ( a[i] > a[j] ) // elementi non ordinativ --> scambia gli elementi
        swap( a[i], a[j] );
}

int
main() {
  int    N = 10000;
  double v[10000];
  Random rgen; // generatore di numeri casuali (mersenne twister)
  TicToc tm;   // orologio per misurare tempi di esecuzione

  /* genezione di un vettore di numeri casuali */
  for ( int i = 0; i < N; ++i )
    v[i] = rgen.dice( -10, 10 ); // restituisce numero casuale nell'intervallo [-10,10]

  tm.tic();
  bubble_sort(v,N);
  tm.toc();

  bool ok = check_if_sorted( v, N );
  if ( ok ) cout << "Ordinamento corretto!\n";
  else      cout << "Ordinamento fallito!\n";

  cout << "Bubble Sort: Elapsed = " << tm.elapsed_ms() << "(ms)\n";

  return 0;
};
