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

// uso solo le funzioni/oggetti che mi servono da namespace std
using std::cout;
using std::cerr;
using std::exception;

class CarRaceField {
  typedef int integer;
  integer nrows, ncols;
  char * board;

public:

  CarRaceField() {
    this->nrows = sizeof(campo)/sizeof(campo[0]);
    this->ncols = strlen(campo[0]);
    this->board = new char[this->nrows*this->ncols];
    for ( integer i = 0; i < this->nrows; ++i )
      for ( integer j = 0; j < this->ncols; ++j )
        this->get(i,j) = campo[i][j];
    cout << "nrows = " << this->nrows << " ncols = " << this-> ncols << '\n';
  }

  ~CarRaceField() {
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

  // accesso elemento (i,j) in lettura/scrittura
  char
  get_for_print( integer i, integer j ) const {
    char c = this->get( i, j );
    if ( c == '@' ) return '.';
    return c;
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
   |  0: posizione libera
   |  1: punto di partenza
   |  2: punto di arrivo
   | -1: muro
   | -2: punto  fuori dal campo
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
   |  0:
   |  1: punto di arrivo
   | -1: muro
   | -2: punto  fuori dal campo
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
   |  0:
   |  1: punto di arrivo
   | -1: muro
   | -2: punto  fuori dal campo
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

    char chmove = '+';
    if ( delta_i > 3*delta_j ) {
      chmove = '|';
    } else if ( delta_j > 3*delta_i ) {
      chmove = '-';
    }

    for ( integer k = 1; k < delta; ++k ) {
      integer i = from_i + integer( (k+0.5)*ri );
      integer j = from_j + integer( (k+0.5)*rj );
      //cout << "i = " << i << " j = " << j << '\n';
      integer res = this->check_position( i, j );
      if ( res < 0 ) return res;
      this->get(i,j) = chmove;
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
      for ( integer j = 0; j < this->ncols; ++j ) stream << " " << this->get_for_print(i,j);
      stream << " |\n";
    }
    stream << '+';
    for ( integer j = 0; j < this->ncols; ++j ) stream << "--";
    stream << "-+\n";
  }
};

class CarRaceCar {
  typedef int integer;

  integer ipos, jpos;
  integer ivel, jvel;

public:

  CarRaceCar() : ipos(0), jpos(0), ivel(0), jvel(0) {
  }

  ~CarRaceCar() {
  }

  /*\
   | posiziona la macchina alla posizione (i,j), ferma
  \*/
  void
  setup( integer i, integer j ) {
    ipos = i;
    jpos = j;
    ivel = jvel = 0;
  }

  /*\
   |
   | accelera la macchia in una possibile direzione
   |
   | 0 = no acceleration
   | 1 = accelerate i-direction
   | 2 = decelerate i-direction
   | 3 = accelerate j-direction
   | 4 = decelerate j-direction
   |
  \*/
  void
  do_acc( integer dir ) {
    switch ( dir ) {
    case 0:         break;
    case 1: ++ivel; break;
    case 2: --ivel; break;
    case 3: ++jvel; break;
    case 4: --jvel; break;
    }
  }

  /*\
   |
   | ritorna il movimeto della machina in base allo stato
   |
  \*/
  void
  get_move( integer & i, integer & j, integer & new_i, integer & new_j ) const {
    i     = ipos;
    j     = jpos;
    new_i = ipos + ivel;
    new_j = jpos + jvel;
  }

  /*\
   |
   | avanza lo stato della macchina
   |
  \*/

  void
  do_step() {
    ipos += ivel;
    jpos += jvel;
  }

};

int
main() {

  try {
    CarRaceField field;
    CarRaceCar   car;

    int move[] = {3,3,3,2,0,1,2,4,4,4,4,2,2};

    car.setup( 26, 0 );

    for ( int kk = 0; kk < 13; ++kk ) {
      car.do_acc( move[kk] );
      int i, j, new_i, new_j;
      car.get_move( i, j, new_i, new_j );
      cout << "i = " << i << " j = " << j
           << " new_i = " << new_i
           << " new_j = " << new_j
           << '\n';
      car.do_step();

      int res = field.do_move( i, j, new_i, new_j );
      cout << "res = " << res << '\n';
      field.plot( cout );
    }
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
