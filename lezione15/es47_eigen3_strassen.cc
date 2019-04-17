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
  Faccio alias su tipo "numero reale".]
  Se cambio idea posso usare

  typedef float real_type;

\*/
typedef double real_type;

/*\

  Uso tyedef per fare degli "alias" che rendono iu leggibile il codice

  Alias predefiniti
  typedef Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> MatriXd;
  typedef Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic>  MatriXf;

\*/

typedef Eigen::Matrix<real_type,Eigen::Dynamic,Eigen::Dynamic> mat;

void
strassen( mat const & A, mat const & B, mat & C ) {

  // le dimensioni devono essere ari

  int n = A.rows();
  int p = A.cols(); // B.nrows()
  int m = B.cols();

  int n2 = n>>1; // n/2
  int p2 = p>>1; // n/2
  int m2 = m>>1; // n/2

  // estrazione sottoblocchi

  // n * p
  mat const & A11 = A.topLeftCorner(n2,p2);
  mat const & A12 = A.topRightCorner(n2,p2);
  mat const & A21 = A.bottomLeftCorner(n2,p2);
  mat const & A22 = A.bottomRightCorner(n2,p2);

  // p * m
  mat const & B11 = B.topLeftCorner(p2,m2);
  mat const & B12 = B.topRightCorner(p2,m2);
  mat const & B21 = B.bottomLeftCorner(p2,m2);
  mat const & B22 = B.bottomRightCorner(p2,m2);

  // allocazione matrice C
  C.resize( n, m );

  mat M1(n2,m2), M2(n2,m2), M3(n2,m2), M4(n2,m2), M5(n2,m2), M6(n2,m2), M7(n2,m2);

  M1 = (A11+A22)*(B11+B22);
  M2 = (A21+A22)*B11;
  M3 = A11*(B12-B22);
  M4 = A22*(B21-B11);
  M5 = (A11+A12)*B22;
  M6 = (A21-A11)*(B11+B12);
  M7 = (A12-A22)*(B21+B22);

  C.topLeftCorner(n2,m2)     = M1+M4-M5+M7;
  C.topRightCorner(n2,m2)    = M3+M5;
  C.bottomLeftCorner(n2,m2)  = M2+M4;
  C.bottomRightCorner(n2,m2) = M1-M2+M3+M6;
}

int
main() {

  try {

    int N = 4;
    mat A, B, C, C1;

    A = mat::Random(N,N);
    B = mat::Random(N,N);
    C = A*B;

    strassen( A, B, C1 );

    if ( N <= 10 ) {
      cout
        << "A  = \n" << A  << "\n\n"
        << "B  = \n" << B  << "\n\n"
        << "C  = \n" << C  << "\n\n"
        << "C1 = \n" << C1 << "\n\n";
    }

    cout << "max elem |C-C1| = " << (C-C1).cwiseAbs().maxCoeff() << "\n\n";

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

