/*

Corsa automobilistica

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <utility>   // STL pair
#include <map>       // STL map class
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <exception> // std::exception
#include <cstdint>   // std::exception

static char const * campo[] = {
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        ",
"          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              @@@@@@@@@@@@@@@",
"     @@@@@@@@@@                                                          2",
"        @@@@@@@@@@@                                                      2",
"                                                          @@@@@@         2",
"                                                     @@@@@@@@@@@         2",
"@@@@@@@@@@@@@@               @@@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@@@   @@@@",
"@@@@@@@@@@@@@@@@@   @@@@     @@@@@@@@@@@@@@@@@     @@@@@@@@@@@@@@@@   @@@@",
"@@@@@@@@@@@@@@@     @@@@@       @@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@    @@@@",
"@@@@@@@@@@       @@@@@@@@              @@@@@@@@@@  @@@@@@@@@@@@@@   @@@@@@",
"@@@@@@@@@         @@@@@@@@@@@@@@                          @@@@@@@  @@@@@@@",
"@@@@@@@@@@@@        @@@@@@@@@@@@@@@@@                  @@@@@@@@@@  @@@@@@@",
"@@@@@@@@@@@@@@@       @@@@@@@@@@@@@@@@@                      @@@@  @@@@@@@",
"@@@@@@@@@@@@@@@        @@@@@@@@@@@@@@@@@@@@@                       @@@@@@@",
"@@@@@@@@@@@@            @@@@@@@@@@@@@@@@@@@@@@@@@@                 @@@@@@@",
"@@@@@@@@@@@@@                                                             ",
"@@@@@@@@@@@@@                                            @@@@@@@@@@@@@@@@@",
"@@@@@@@@                     @@@@@@@                @@@@@@@@@@@@@@@@@@@@@@",
"@@@@@@@@@@@@@                @@   @@               @@@@@@@@@@@@@@@@@@@@@@@",
"@@@@@@@@@@@@@                @@@@@@@              @@@@@@@@@@@@@@@@@@@@@@@@",
"@@@@@@@@@@@@@                                     @@@@@@@@@@@@@@@@@@@@@@@@",
"@@@@@  @@@@@@                                        @@@@@@@@@@@@@@@@@@@@@",
"@@@@@  @@@@@@                                                             ",
"1       @@@@@@         @@@@@                                              ",
"1                        @@@@@                                            ",
"1            @@                                                           ",
"1          @@                                                             ",
"@@@@@@@@@           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
"@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
};

// uso solo le fuzioni/oggetti che mi servono da namespace std
using std::cout;
using std::cerr;
using std::exception;

class CarRace {
  typedef int integer;
  integer nrows, ncols;
  char * board;

public:

  CarRace() {
    this->nrows = sizeof(campo)/sizeof(campo[0]);
    this->ncols = strlen(campo[0]);
    this->board = new char[this->nrows*this->ncols];
    for ( integer i = 0; i < this->nrows; ++i )
      for ( integer j = 0; j < this->ncols; ++j )
        this->get(i,j) = campo[i][j];
    cout << "nrows = " << this->nrows << " ncols = " << this-> ncols << '\n';
  }

  ~CarRace() {
    delete this->board;
  }

  // accesso elemento (i,j) in sola lettura
  char
  get( integer i, integer j ) const {
    return board[i+j*this->nrows];
  }

  // accesso elemento (i,j) in lettura/scrittura
  char &
  get( integer i, integer j ) {
    return board[i+j*this->nrows];
  }

  // accesso elemento (i,j) in sola lettura
  char
  operator () ( integer i, integer j ) const {
    return board[i+j*this->nrows];
  }

  // accesso elemento (i,j) in lettura/scrittura
  char &
  operator () ( integer i, integer j ) {
    return board[i+j*this->nrows];
  }

  /*\
     0: posizione libera
     1: punto di partenza
     2: punto di arrivo
    -1: muro
    -2: punto  fuori dal campo
  \*/
  integer
  check_position( integer i, integer j ) const {
    if ( i < 0 || i >= this->nrows || j < 0 || j >= this->ncols ) return -2;
    char elem = this->get(i,j);
    if ( elem == '1' ) return 1;
    if ( elem == '2' ) return 2;
    if ( elem == '@' ) return -1;
    return 0;
  }

  /*\
     0:
     1: punto di arrivo
    -1: muro
    -2: punto  fuori dal campo
  \*/

  integer
  check_move(
    integer from_i,
    integer from_j,
    integer to_i,
    integer to_j
  ) const {
    integer delta_i = std::abs(from_i-to_i);
    integer delta_j = std::abs(from_j-to_j);
    integer delta   = std::max( delta_i, delta_j );

    double ri = double(to_i-from_i)/delta;
    double rj = double(to_j-from_j)/delta;

    for ( integer k = 0; k <= delta; ++k ) {
      integer i = from_i + integer( (k+0.5)*ri );
      integer j = from_j + integer( (k+0.5)*rj );
      //cout << "i = " << i << " j = " << j << '\n';
      integer res = this->check_position( i, j );
      if ( res < 0 ) return res;
    }
    return 0;
  }

  /*\
     0:
     1: punto di arrivo
    -1: muro
    -2: punto  fuori dal campo
  \*/
  integer
  do_move(
    integer from_i,
    integer from_j,
    integer to_i,
    integer to_j
  ) {
    integer delta_i = std::abs(from_i-to_i);
    integer delta_j = std::abs(from_j-to_j);
    integer delta   = std::max( delta_i, delta_j );

    double ri = double(to_i-from_i)/delta;
    double rj = double(to_j-from_j)/delta;

    for ( integer k = 1; k < delta; ++k ) {
      integer i = from_i + integer( (k+0.5)*ri );
      integer j = from_j + integer( (k+0.5)*rj );
      //cout << "i = " << i << " j = " << j << '\n';
      integer res = this->check_position( i, j );
      if ( res < 0 ) return res;
      this->get(i,j) = '+';
    }
    this->get(from_i,from_j) = 'o';
    this->get(to_i,to_j)     = 'o';
    return 0;
  }

  void
  plot( std::ostream & stream ) const {
    stream << '+';
    for ( integer j = 0; j < this->ncols; ++j ) stream << "--";
    stream << "-+\n";
    for ( integer i = 0; i < this->nrows; ++i ) {
      stream << '|';
      for ( integer j = 0; j < this->ncols; ++j ) stream << " " << this->get(i,j);
      stream << " |\n";
    }
    stream << '+';
    for ( integer j = 0; j < this->ncols; ++j ) stream << "--";
    stream << "-+\n";
  }
};

int
main() {

  try {
    CarRace cr;

    int res = cr.do_move( 26, 0, 24, 7 );
    cout << "res = " << res << '\n';
    cr.plot( cout );

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
