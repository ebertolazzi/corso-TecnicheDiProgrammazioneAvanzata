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

int
trenp1( int n ) {
  cout << "n = " << n << '\n';
  // if ( (n&0x01) == 0 ) {
  if ( n == 1 ) return 0;
  if ( (n % 2) == 0 ) { // pari
    static int tmp = n/2;
    return trenp1(tmp);
  } else {
    static int tmp = 3*n+1;
    return trenp1(tmp);
  }
}

int
main() {
  trenp1(100);
  trenp1(1000);
  return 0;
};
