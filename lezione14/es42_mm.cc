/*
  A simple program to test string class
 */

#include "course_lib.h"

#include <iostream> // for I/O
#include <iomanip>  // for hex, dec, width
#include <string>   // string support

// carico namespace std per evitare di scrivere std:: ogni volta
// che uso una funzione di std.
using namespace std;

/*\
  Funzione indirizzamento per matrice column major
\*/
inline // funzione espansa "come fosse una macro" (no overhead)
unsigned
addr( unsigned i, unsigned j, unsigned ldim ) {
  return i+j*ldim;
}

/*\

 Riempie matrice A con numeri casuali

\*/
template <typename Type>
static
void
fillRandom( Type A[], unsigned ldA, unsigned n, unsigned m ) {
  Random nc;
  for ( unsigned i = 0 ; i < n ; ++i )
    for ( unsigned j = 0 ; j < m ; ++j )
      A[addr(i,j,ldA)] = nc.dice( -1000, 1000 );
}

/*\
  A matrice n*p
  B matrice p*m
  C matrice n*m (risulatato)
\*/
template <typename Type>
void
mm_standard(
  Type const A[], unsigned ldA,
  Type const B[], unsigned ldB,
  Type       C[], unsigned ldC,
  unsigned n, // number of the rows of A
  unsigned p, // number of the columns of A and rows of B
  unsigned m  // number of the columns of B
              // the results is a matrix C of n rows and m co
) {
  // prodotto standard
  for ( unsigned i = 0; i < n; ++i ) {
    for ( unsigned j = 0; j < m; ++j ) {
      C[addr(i,j,ldC)] = 0;
      for ( unsigned k = 0; k < p; ++k )
        C[addr(i,j,ldC)] += A[addr(i,k,ldA)]*B[addr(k,j,ldB)];
    }
  }
}


int
main( int argc, char const * argv[] ) {
  // leggo dimensione matrici da linea di comando
  // comando n p m oppure solo un numero nel caso n=m=p
  unsigned n, p, m;
  if ( argc == 2 ) {
    sscanf( argv[1], "%d", &n );
    p = m = n;
  } else if ( argc == 4 ) {
    sscanf( argv[1], "%d", &n );
    sscanf( argv[2], "%d", &p );
    sscanf( argv[3], "%d", &m );
  } else {
    cerr
      << "usage: " << argv[0] << " n p m\n"
      << "or: " << argv[0] << " n\n" ;
    return 1;
  }

  // allocazione dinamica
  double * ptr;
  AutoAllocate<double> mem( n*p + p*m + n*m, &ptr);
  double * A = ptr; ptr += n*p;
  double * B = ptr; ptr += p*m;
  double * C = ptr; // ptr += n*m;

  // ijnizializziamo matrici A e B
  fillRandom( A, n, n, p );
  fillRandom( B, p, p, m );

  TicToc tm;

  tm.tic();
  mm_standard( A, n, B, p, C, n, n, p, m );
  tm.toc();

  cout << "Elapsed time = " << tm.elapsed_ms() << " ms\n";

  // in uscita mem chiama il suo distruttore e rilascia la memoria
  return 0;
}

