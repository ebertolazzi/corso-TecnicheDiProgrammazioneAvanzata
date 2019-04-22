/*\

  Calcolo a^n con n intero in maniera efficiente.

  n = n0 + n1*2 + n2*2^2 + .... + nk * 2^k

  a^n = a0 * a1 * a2 * ... * ak

  dove ai = a^(2^i) se ni = 1
       a1 = 1       se ni = 0

  ai sono calcolati mediante elevando al quadrato
  a i volte.

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <vector>    // STL vector class
#include <map>       // STL map class
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <exception> // std::exception
#include <cstdint>   // std::exception

using std::cerr;

// uso interi a 64 bit (molto grandi)
// 18446744073709551615 (massimo numero intero per uint64_t)]

/*
// Versione con "memo(r)ization"
//
// Per memorizzare uso oggetto contenitore map<uint64_t,uint64_t>
// dove
//   chiave = n
//   valire = F(n)
*/

template <typename T>
void
power( T const & a, T & res, int n ) {
  // res in chiamata deve essere messo a 1 (o equivalente)
  T asqr = a;
  while ( n > 0 ) {
    if ( (n & 0x1) == 1 ) res *= asqr;
    n     = n>>1;
    asqr *= asqr;
  }
}

// uso solo le funzioni/oggetti che mi servono da namespace std
using std::cout;
using std::cerr;
using std::exception;

int
main() {

  try {
    long a   = 2;
    long res = 2;
    power( a, res, 6 );
    cout << "2^6 = " << res << '\n' ;
  }
  catch ( exception const & error ) {
    cerr << "Exception number " << error.what() << "\n\n";
  }
  catch ( ... ) {
    cerr << "Exception found: Unknown error\n"  ;
  }
  cout << "END OF PROGRAM\n" ;

  return 0 ;
}

