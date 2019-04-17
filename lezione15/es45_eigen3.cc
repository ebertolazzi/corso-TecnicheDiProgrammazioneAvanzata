/*
  Esemio di uso della libreria Eigen3

 -I/usr/local/include/eigen3  to add search of headers for eigen3 library

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <vector>    // STL vector class
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <exception> // std::exception

// include headers for the Dense linear algebra of Eigen library
#include <Eigen/Dense>

using namespace std;
//using namespace Eigen;

/*\
 Funzione lineare per generare tabella di dati
\*/

template <typename T>
T
func( T x )
{ return 10*x-3; }

/*\

  Costruisco tabella dei punti (xi,yi).
  Uso vector di STL per mostrare che STL e Eigen3 convivono felicente.

\*/

template <typename T>
void
generate_table( vector<T> & x,
                vector<T> & y,
                int         N ) {
  x.clear();
  y.clear();
  x.reserve(N);
  y.reserve(N);

  Random nc;

  for ( int i = 0 ; i < N ; ++i ) {
    T xx = nc.dice( -5000, 5000 );
    T yy = func(xx);
    // aggiungo perturbazione
    yy += nc.dice( -5, 5 );
    // aggiungo in coda il punto
    x.push_back(xx) ;
    y.push_back(yy) ;
  }
}

/*\
  Faccio alias su tipo "numero reale".]
  Se cambio idea posso usare

  typedef float real_type;

\*/
typedef double real_type;

int
main() {

  try {

    // uso na milionata de punti
    int N = 1000000 ;
    vector<real_type> x, y ;
    generate_table( x, y, N ) ;

    // defnisce una matrice 2x2 con elementi tipo double
    Eigen::Matrix2d A ;
    // defnisce due vettori dimension 2 con elementi tipo double
    Eigen::Vector2d b, sol ;

    /* costruzione elementi matrice, maniera "becera" */
    // sum xi*xi
    real_type bf = 0 ;
    for ( int i = 0 ; i < N ; ++i ) bf += x[i]*x[i];
    A(0,0) = bf;

    // sum xi
    bf = 0 ;
    for ( int i = 0 ; i < N ; ++i ) bf += x[i];
    A(1,0) = A(0,1) = bf;
    A(1,1) = N;

    // sum xi*yi
    bf = 0 ;
    for ( int i = 0 ; i < N ; ++i ) bf += x[i]*y[i];
    b(0) = bf;

    // sum yi
    bf = 0 ;
    for ( int i = 0 ; i < N ; ++i ) bf += y[i];
    b(1) = bf;

    cout
      << "Sistema lineare da risolvere:\n"
      << "A =\n" << A << "\n\n"
      << "b =\n" << b << "\n\n";

    /*\
      So che la matrice è simmetrica e definita positiva,
      posso usare metodo di Cholewsky al posto della
      eliminazione di Gauss (costa meno).
    \*/

    // use Cholewsky decomposition
    /*\
     L'oggetto LLT della libreria Eigen3 costruisce
     la fattorizzazione di Cholewsky della matrice
     passata al suo costruttore.

     A = L * L^T

     L = matrice trinagolare inferiore

    \*/
    Eigen::LLT<Eigen::Matrix2d> LLT_of_matrix_A(A);
    /*\
     LLT_of_matrix_A contiene la fattorizzazione della matrice A

     Non importa come è memorizzata, calcolata etc.
     Basta usare i metodi che l'oggetto vi mette a dispozione.

    \*/

    // il metodo solve(b) --> risolve il sistema L*L^T x = b
    sol = LLT_of_matrix_A.solve(b);

    // sol è soluzione del sistema A * x = b

    cout << "Solution = " << sol.transpose() << '\n' ;

  }
  catch ( exception const & error ) {
    cerr << "Exception number " << error.what() << "\n"  ;
  }
  catch ( ... ) {
    cerr << "Exception found: Unknown error\n"  ;
  }
  cout << "END OF PROGRAM\n" ;

  return 0 ;
}

