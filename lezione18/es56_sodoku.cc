/*\

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <fstream>   // lettura/scrittura su file
#include <sstream>   // lettura/scrittura su stringa
#include <utility>   // STL pair
#include <set>       // STL set object
#include <algorithm> // STD std::transform
#include <string>    // STL string
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <exception> // std::exception
#include <cstdint>   // std::exception

using namespace std;

/*\

  controlla scacchiera sodoku

  1  = ok gioco terminato
  0  = ok ma ancora elementi da inserire (0=elemento da inserire)
  -1 = trovato numero fuori del range [0,1,...,9]
  -2 = scacchiera inconsistente
\*/

static
int
check_sodoku( unsigned board[9][9], bool debug ) {
  unsigned countR[10], countC[10], count[10];
  // check cols rows
  int ret = 1; // ok
  for ( unsigned i = 0; i < 9; ++i) {
    std::fill( countR, countR+10, 0 );
    std::fill( countC, countC+10, 0 );
    for ( unsigned j = 0; j < 9; ++j ) {
      unsigned bij = board[i][j];
      unsigned bji = board[j][i];
      if ( bij > 9 || bji > 9 ) return -1;
      ++countR[bij];
      ++countC[bji];
    }
    // se riga ok deve essere count = {0,1,1,1,1,1,1,1,1,1}
    for ( unsigned j = 1; j <= 9; ++j ) {
      if ( countR[j] > 1 ) {
        if ( debug )
          cout
            << "row " << i << " count = [ "
            << countR[0] << " "
            << countR[1] << " "
            << countR[2] << " "
            << countR[3] << " "
            << countR[4] << " "
            << countR[5] << " "
            << countR[6] << " "
            << countR[7] << " "
            << countR[8] << " "
            << countR[9] << "]\n";
        return -2; // piu di un numero sulla stessa riga/colonna
      }
      if ( countC[j] > 1 )  {
        if ( debug )
          cout
            << "col " << i << " count = [ "
            << countC[0] << " "
            << countC[1] << " "
            << countC[2] << " "
            << countC[3] << " "
            << countC[4] << " "
            << countC[5] << " "
            << countC[6] << " "
            << countC[7] << " "
            << countC[8] << " "
            << countC[9] << "]\n";
        return -2; // piu di un numero sulla stessa riga/colonna
      }
    }
    if ( countR[0] > 0 || countC[0] > 0 ) ret = 0; // qualche elemento ancora da assegnare
  }

  // check squares
  for ( unsigned ii = 0; ii < 3; ++ii ) {
    for ( unsigned jj = 0; jj < 3; ++jj ) {
      std::fill( count, count+10, 0 );
      for ( unsigned i = 0; i < 3; ++i) {
        for ( unsigned j = 0; j < 3; ++j ) {
          unsigned bij = board[3*ii+i][3*jj+j];
          if ( bij > 9 ) return -1;
         ++count[bij];
        }
      }
      // se quadrato ok deve essere count = {0,1,1,1,1,1,1,1,1,1}
      for ( unsigned j = 1; j <= 9; ++j )
        if ( count[j] > 1 ) {
          if ( debug )
            cout
              << "block " << ii << " " << jj << " count = [ "
              << count[0] << " "
              << count[1] << " "
              << count[2] << " "
              << count[3] << " "
              << count[4] << " "
              << count[5] << " "
              << count[6] << " "
              << count[7] << " "
              << count[8] << " "
              << count[9] << "]\n";
          return -2; // piu di un numero sullo stesso quadrato
        }
      if ( count[0] > 0 ) ret = 0; // qualche elemento ancora da assegnare
    }
  }
  return ret;
}

static
void
plot_sodoku( ostream & stream, unsigned board[9][9] ) {
  char const *nums[] = {
    " . ", " 1 ", " 2 "," 3 "," 4 "," 5 "," 6 "," 7 "," 8 "," 9 "
  };
  // check cols rows
  for ( unsigned i = 0; i < 9; ++i) {
    if ( (i % 3) == 0 ) stream << "+---------+---------+---------+\n";
    for ( unsigned j = 0; j < 9; ++j ) {
      if ( (j % 3) == 0 ) stream << "|";
      stream << nums[board[i][j]];
    }
    stream << "|\n";
  }
  stream << "+---------+---------+---------+\n";
}

unsigned example[9][9] = {
  { 0, 0, 0,  9, 0, 4,  0, 0, 1 },
  { 0, 2, 0,  3, 0, 0,  0, 5, 0 },
  { 9, 0, 6,  0, 0, 0,  0, 0, 0 },

  { 8, 0, 0,  0, 4, 6,  0, 0, 0 },
  { 4, 0, 0,  0, 1, 0,  0, 0, 3 },
  { 0, 0, 0,  2, 7, 0,  0, 0, 5 },

  { 0, 0, 0,  0, 0, 0,  9, 0, 7 },
  { 0, 7, 0,  0, 0, 5,  0, 1, 0 },
  { 3, 0, 0,  4, 0, 7,  0, 0, 0 }
};

int
main() {

  try {
    plot_sodoku( cout, example );
    int ok = check_sodoku( example, false );
    cout << "ok = " << ok << "\n";

  }
  catch ( string const & error ) {
    cerr << "Errore: " << error << "\n\n";
  }
  catch ( exception const & error ) {
    cerr << "Exception: " << error.what() << "\n\n";
  }
  catch ( ... ) {
    cerr << "Exception found: Unknown error\n"  ;
  }
  cout << "END OF PROGRAM\n" ;

  return 0 ;
}
