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

/*\
  restituisce un vettore (vector<int>) con
  l'elenco  dei numeri primi <= N
\*/
void
crivello_eratostene( int Nmin, int Nmax, vector<int> & primi ) {
  // uso vettore di booleani
  vector<bool> is_a_prime(Nmax+1); // alloco vettore a dimensione N+1
  // inizializzo (tutti i numeri sono numeri primi...)
  for ( int i = 0; i <= Nmax; ++i ) is_a_prime[i] = true;
  // modo usando primitive STL
  std::fill( is_a_prime.begin(), is_a_prime.end(), true );

  int nprimi = 0;
  for ( int i = 2; i <= Nmax; ++i ) {
    if ( is_a_prime[i] ) {
      if ( i >= Nmin ) ++nprimi; // trovato primo
      // eliminare i multipli da essere primi...
      for ( int j = i+i; j <= Nmax; j += i )
        is_a_prime[j] = false;
    }
  }

  // piu elegante
  primi.clear();
  primi.reserve( nprimi );
  for ( int i = Nmin; i <= Nmax; ++i )
    if ( is_a_prime[i] )
      primi.push_back(i);
}
