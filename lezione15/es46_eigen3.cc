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

/*\
  Faccio alias su tipo "numero reale".]
  Se cambio idea posso usare

  typedef float real_type;

\*/
typedef double real_type;

/*\

  Uso tyedef per fare degli "alias" che rendono iu leggibile il codice

\*/
typedef Eigen::Matrix<real_type,Eigen::Dynamic,1> vec;
typedef Eigen::Matrix<real_type,2,2>              mat2x2;
typedef Eigen::Matrix<real_type,2,1>              vec2;

void
generate_table( vec & x, vec & y, int N ) {
  x.resize(N);
  y.resize(N);

  Random nc;

  for ( int i = 0 ; i < N ; ++i ) {
    real_type xx = nc.dice( -5000, 5000 );
    real_type yy = func(xx);
    // aggiungo perturbazione
    yy += nc.dice( -50, 50 );
    // aggiungo in coda il punto
    x(i) = xx;
    y(i) = yy;
  }
}

int
main() {

  try {

    // uso na milionata de punti
    int N = 100000000;
    vec x, y;
    generate_table( x, y, N );

    // defnisce una matrice 2x2 con elementi tipo double
    mat2x2 A;
    // defnisce due vettori dimension 2 con elementi tipo double
    vec2 b, sol;

    // sum xi*xi
    // x.dot(y) fa prodotto scalare del vettore x con il vettore y
    A(0,0) = x.dot(x);

    // sum xi
    // x.sum() restituisce la somma degli elementi del vettore
    A(1,0) = A(0,1) = x.sum();
    A(1,1) = N;

    // sum xi*yi
    b(0) = x.dot(y) ;

    // sum yi
    b(1) = y.sum() ;

    cout
      << "Sistema lineare da risolvere:\n"
      << "A =\n" << A << "\n\n"
      << "b =\n" << b << "\n\n";

    // use Cholewsky decomposition
    Eigen::LLT<mat2x2> LLT_of_matrix_A(A) ;
    sol = LLT_of_matrix_A.solve(b) ;
    cout << "Solution = " << sol << '\n' ;

    // solve the problem using least squares
    Eigen::Matrix<real_type,Eigen::Dynamic,Eigen::Dynamic> Mat(N,2);
    Eigen::Matrix<real_type,Eigen::Dynamic,1>              Rhs(N);
    // riempio prima colonna di Mat con il vettore x
    Mat.col(0) = x;

    // riempio seconda colonna di Mat con il numero 1
    Mat.col(1).fill(1) ; // fill column with one's

    // la r.h.s vale y
    for ( int i = 0; i < N; ++i ) Rhs(i) = y[i];

    // controllo che Mat^T * Mat == A
    cout << "Mat^T * Mat =\n" << Mat.transpose() * Mat << "\n\n";
    cout << "A           =\n" << A << "\n\n";

    // invece che costruire oggetto fattorizzazione QR
    // restiuisco oggetto temporaneo Mat.colPivHouseholderQr()
    // fattorizzazione QR della matrice Mat
    // lo uso chiamando solve e dopo l'uso viene distrutto.
    sol = Mat.colPivHouseholderQr().solve(Rhs);

    cout << "Solution (LS) = " << sol << "\n\n";

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

