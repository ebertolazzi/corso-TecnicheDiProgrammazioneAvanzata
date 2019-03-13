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
crivello_eratostene( int N, vector<int> & primi ) {
  // uso vettore di booleani
  vector<bool> is_a_prime(N+1); // alloco vettore a dimensione N+1
  // inizializzo (tutti i numeri sono numeri primi...)
  for ( int i = 0; i <= N; ++i ) is_a_prime[i] = true;
  // modo usando primitive STL
  std::fill( is_a_prime.begin(), is_a_prime.end(), true );

  int nprimi = 2;
  for ( int i = 2; i <= N; ++i ) {
    if ( is_a_prime[i] ) {
      ++nprimi; // trovato primo
      // eliminare i multipli da essere primi...
    }
  }

  // fare loop
  primi.resize( nprimi );
  // loop per riempire i numeri primi

  // piu elegante
  primi.reserve( nprimi );
  // loop con primi.push_back(...);

}

int
main() {
  int N = 1000;
  vector<int> primi;
  TicToc tm;

  tm.tic();
  crivello_eratostene( N, primi );
  tm.toc();

  // stampa numeri primi
  for ( int i = 0; i < N; ++i ) {
    cout << setw(8) << primi[i];
    if ( (i % 10) == 0 ) cout << '\n' ;
    else                 cout << ' ';
  }

  cout << "Elapsed (eratostene) = " << tm.elapsed_ms() << "(ms)\n";

  return 0;
};
