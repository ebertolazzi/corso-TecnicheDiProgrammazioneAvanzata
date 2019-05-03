/*

Corsa automobilistica

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <utility>   // STL pair
#include <map>       // STL map
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <exception> // std::exception
#include <cstdint>   // std::exception

/*\

Calcolo "Edit distance" pag 17 libro Algorithm Jeff ...


\*/

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::ostream;
using std::map;
using std::pair;

class Edit {

  // dichiaro mutable count per poterlo incrementare
  // nei metodi dichiarati const
  mutable unsigned long count;
  string   a_stored; // stringhe da confrontare
  string   b_stored;
  unsigned dst;

  // funzione privata
  unsigned
  edit( int lena, int lenb ) {
    ++this->count;
    if ( lenb == 0 ) return lena;
    if ( lena == 0 ) return lenb;

    unsigned d1 = this->edit( lena,   lenb-1 ) + 1;
    unsigned d2 = this->edit( lena-1, lenb ) + 1;
    unsigned d3 = this->edit( lena-1, lenb-1 );
    if ( this->a_stored[lena-1] != this->b_stored[lenb-1] ) ++d3; // se ultimo carattere diverso incremento
    // prendo minimo delle distanze
    unsigned d = d1;
    if ( d > d2 ) d = d2;
    if ( d > d3 ) d = d3;
    return d;
  }

  map<pair<unsigned,unsigned>,unsigned> stored_sub_distance;

public:

  Edit() : count(0), a_stored(""), b_stored(""), dst(0) {}

  void
  setup( string const & a, string const & b ) {
    this->count    = 0;
    this->a_stored = a;
    this->b_stored = b;
    this->dst      = this->edit( this->a_stored.size(), this->b_stored.size() );
  }

  void
  info( ostream & stream ) const {
    stream
      << "distance = " << this->dst
      << " count = " << this->count
      << '\n';
  }

};

int
main() {

  try {
    Edit e;
    //string a = "precipitevolissimevolmente";
    //string b = "supercalifragilestichespiralitoso";
    string a = "pippo";
    string b = "paperino";
    e.setup(a,b);
    e.info( cout );
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
