/*\

Calcolo "Edit distance" pag 17 libro Algorithm di Jeff Erickson

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <utility>   // STL pair
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <exception> // std::exception
#include <cstdint>   // std::exception

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::ostream;
using std::vector;
using std::pair;

class Edit {

  string   a_stored; // stringhe da confrontare
  string   b_stored;
  unsigned la, lb;
  unsigned dst;
  vector<unsigned> dst_matrix;

public:

  Edit() : a_stored(""), b_stored(""), dst(0) {}

  unsigned &
  edit( unsigned i, unsigned j )
  { return dst_matrix[i+j*(this->la+1)]; }

  unsigned const &
  edit( unsigned i, unsigned j ) const
  { return dst_matrix[i+j*(this->la+1)]; }

  void
  setup( string const & a, string const & b ) {
    this->a_stored = a;
    this->b_stored = b;
    this->la       = a.size();
    this->lb       = b.size();
    dst_matrix.resize( (this->la+1) * (this->lb+1) );
    // riempio matrice
    for ( unsigned i = 0; i <= this->la; ++i )
      this->edit( i, 0 ) = i;
    for ( unsigned j = 1; j <= this->lb; ++j )
      this->edit( 0, j ) = j;

    for ( unsigned i = 1; i <= this->la; ++i ) {
      for ( unsigned j = 1; j <= this->lb; ++j ) {
        unsigned d1 = this->edit( i, j-1 ) + 1;
        unsigned d2 = this->edit( i-1, j ) + 1;
        unsigned d3 = this->edit( i-1, j-1 );
        if ( this->a_stored[i-1] != this->b_stored[j-1] ) ++d3; // se ultimo carattere diverso incremento
        // prendo minimo delle distanze
        unsigned d = d1;
        if ( d > d2 ) d = d2;
        if ( d > d3 ) d = d3;
        this->edit( i, j ) = d;
      }
    }
    dst = this->edit(this->la,this->lb);
  }

  void
  info( ostream & stream ) const {
    stream
      << "distance = " << this->dst
      << '\n';
  }

};

int
main() {

  try {
    Edit e;
    string a = "precipitevolissimevolmente";
    string b = "supercalifragilestichespiralitoso";
    //string b = "pippo";
    //string b = "paperino";
    cout << "|a| = " << a.size() << '\n';
    cout << "|b| = " << b.size() << '\n';
    cout << "(|a|+1) * (|b|+1) = " << (a.size()+1)*(b.size()+1) << '\n';
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
