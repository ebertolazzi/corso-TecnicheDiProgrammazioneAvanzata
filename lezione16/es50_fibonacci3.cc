/*
Confronto Fibonacci, metodo ricorsivo VS metodo iterativo com "memoization"

Uso di una ricorsione migliorata, che si trova al capitolo 3
del libro Algorithms by Jeff Erickson

http://jeffe.cs.illinois.edu/teaching/algorithms/book/03-dynprog.pdf

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
typedef std::map<uint64_t,uint64_t> map_ii;

uint64_t
Fibonacci_with_memoization( uint64_t n, map_ii & F_stored ) {

  uint64_t N, Fp0, Fp1, Fn;
  map_ii::iterator i0, i1;

  switch ( n ) {
  case 0: // caso n == 0
    F_stored[0] = 0; // aggiungo elemento alla mappa
    return 0;
  case 1: // caso n == 1
    F_stored[1] = 1; // aggiungo elemento alla mappa
    return 1;
  default: // caso n >= 2
    // scrivo n = 2*N o 2*N -1
    bool is_even = (n & 0x1) == 0;
    N = is_even ? n>>1 : 1+(n>>1);
    // n = 2*N se pari o n = 2*N-1 se dispari

    // controllo se elemento è gia presente nella mappa, alttimenti lo calcolo
    i0 = F_stored.find( N );
    if ( i0 == F_stored.end() ) {
      // elemento non trovato, lo calcolo
      Fp0 = F_stored[N] = Fibonacci_with_memoization( N, F_stored );
    } else {
      // elemento trovato, lo leggo
      Fp0 = i0->second; // first = chiave, second = valore
    }
    i1 = F_stored.find( N-1u );
    if ( i1 == F_stored.end() ) {
      // elemento non trovato, lo calcolo
      Fp1 = F_stored[N-1u] = Fibonacci_with_memoization( N-1u, F_stored );
    } else {
      // elemento trovato, lo leggo
      Fp1 = i1->second; // first = chiave, second = valore
    }

    // calcolo e memorizzo nuovo valore
    if ( is_even ) {
      Fn = Fp0*(2*Fp1+Fp0);
    } else {
      Fn = Fp0*Fp0+Fp1*Fp1;
    }
    F_stored[n] = Fn;
    return Fn;
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
      Fn = Fnm1+Fnm2;
      if ( k > 2 && (Fn <= Fnm1 || Fn <= Fnm2) ) {
        cerr << "Overflow!\n";
      }
      Fnm2 = Fnm1;
      Fnm1 = Fn;
    }
    return Fn;
  }
}

// uso solo le funzioni/oggetti che mi servono da namespace std
using std::cout;
using std::cerr;
using std::exception;

int
main() {

  try {

    TicToc tm;
    uint64_t F[] = {10, 20, 30, 45, 90};
    uint64_t res[10];

    for ( int i = 0; i < 5; ++i ) {
      tm.tic();
      map_ii F_stored;
      for ( int kkk = 0; kkk < 100; ++kkk ) {
        res[0] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[1] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[2] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[3] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[4] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[5] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[6] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[7] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[8] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
        res[9] = Fibonacci_with_memoization(F[i],F_stored);
        F_stored.clear();
      }
      tm.toc();

      res[0] = Fibonacci_with_memoization(F[i],F_stored);

      cout << "SIZE TABLE = " << F_stored.size() << "\n";

      cout
        << "Fibonacci_with_memoization(" << F[i] << ") = " << res[0]
        << " elapsed = " << tm.elapsed_ms()
        << "(ms)\n\n";

      tm.tic();
      for ( int kkk = 0; kkk < 100; ++kkk ) {
        res[0] = Fibonacci_iterative(F[i]);
        res[1] = Fibonacci_iterative(F[i]);
        res[2] = Fibonacci_iterative(F[i]);
        res[3] = Fibonacci_iterative(F[i]);
        res[4] = Fibonacci_iterative(F[i]);
        res[5] = Fibonacci_iterative(F[i]);
        res[6] = Fibonacci_iterative(F[i]);
        res[7] = Fibonacci_iterative(F[i]);
        res[8] = Fibonacci_iterative(F[i]);
        res[9] = Fibonacci_iterative(F[i]);
      }
      tm.toc();
      cout
        << "Fibonacci_iterative(" << F[i] << ") = " << res[0]
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

