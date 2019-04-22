/*

Confronto Fibonacci, metodo ricorsivo VS metodo iterativo

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <vector>    // STL vector class
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <exception> // std::exception
#include <cstdint>   // std::exception

// uso interi a 64 bit (molto grandi)
// 18446744073709551615 (massimo numero intero per uint64_t)]

// Versione ricorsiva
uint64_t
Fibonacci_with_recurrence( uint64_t n ) {
  switch ( n ) {
  case 0: // caso n == 0
    return 0;
  case 1: // caso n == 1
    return 1;
  default: // caso n >= 2
    // 1u = intero unsigned --> impedisce di convertire a intero con segno la valutazione
    return Fibonacci_with_recurrence(n-1u)+Fibonacci_with_recurrence(n-2u);
  }
}

// versione iterativa
uint64_t
Fibonacci_iterative( uint64_t n ) {
  uint64_t Fnm2 = 0;
  uint64_t Fnm1 = 1;
  switch ( n ) {
  case 0: // caso n == 0
    return 0;
  case 1: // caso n == 1
    return 1;
  default: // caso n >= 2
    uint64_t Fn;
    for ( int k = 2; k <= n; ++k ) {
      Fn   = Fnm1+Fnm2;
      Fnm2 = Fnm1;
      Fnm1 = Fn;
    }
    return Fn;
  }
}

// uso solo le fuzioni/oggetti che mi servono da namespace std
using std::cout;
using std::cerr;
using std::exception;

int
main() {

  try {

    TicToc tm;
    uint64_t F[] = {10, 20, 30, 40, 45};
    uint64_t res;

    for ( int i = 0; i < 5; ++i ) {
      tm.tic();
      res = Fibonacci_with_recurrence(F[i]);
      tm.toc();
      cout
        << "Fibonacci_with_recurrence(" << F[i] << ") = " << res
        << " elapsed = " << tm.elapsed_ms()
        << "(ms)\n\n";

      tm.tic();
      res = Fibonacci_iterative(F[i]);
      tm.toc();
      cout
        << "Fibonacci_iterative(" << F[i] << ") = " << res
        << " elapsed = " << tm.elapsed_ms()
        << "(ms)\n\n";

    }

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

