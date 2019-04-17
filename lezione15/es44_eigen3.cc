/*
  Esemio di uso della libreria Eigen3

 -I/usr/local/include/eigen3  to add search of headers for eigen3 library

\*/

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

int
main() {

  try {

    // defnisce una matrice 2x2 con elementi tipo double
    // Matrix2d = Matrix<double,2,2>
    //                     ^    ^ ^
    //         tipo -------+    | |
    //         numero righe  ---+ |
    //         numero colonne  ---+
    Eigen::Matrix2d a;

    // inizializzare gli elementi di a usando operatore << e operatore ,
    a << 1, 2,
         3, 4;

    /*\
    equivalente a inizializzare come segue
    a(0,0) = 1;
    a(0,1) = 2;
    a(1,0) = 3;
    a(1,1) = 4;
    \*/

    // defnisce una matrice nxm con elementi tipo double
    // MatrixXd = Matrix<double,Dynamic,Dynamic>
    //                     ^       ^       ^
    //         tipo -------+       |       |
    // num. righe non specificato -+       |
    // num. colonne non specificato -------+
    // uso il costruttorer che specifica (runtime) le dimensioni della matrice
    Eigen::MatrixXd b(2,2);
    // le dimensioni della matrice possono essere cambiate sucessivamente
    // (le matrice viene riallocata)

    // inizializzare gli elementi di a usando operatore << e operatore ,
    b << 2, 3,
         1, 4;

    /*\

      Gli operatori + * - etc sono definiti per l'oggetto Matrix di Eigen3
      e (per la maggioranza) si comportano come uso si aspetta.

    \*/

    cout << "a =\n" << a << "\n\n";
    cout << "b =\n" << b << "\n\n";

    cout << "a + b =\n" << a + b << "\n\n";
    cout << "a - b =\n" << a - b << "\n\n";

    cout << "Doing a += b;" << "\n\n";
    // alla matrice a sommo la matrice b
    a += b;
    cout << "Now a =\n" << a << "\n\n";

    // i vettori sono casi partivolari di matrici
    // Vector3d = Matrix<double,3,1>
    // definisce vettoe di 3 elementi di tio double
    // esiste costruttore per vettori 3d che inizializza il vettore
    // con i suoi valori
    Eigen::Vector3d v(1,2,3); // v << 1 << 2 << 3 ;
    Eigen::Vector3d w(1,0,0); // v << 1 << 0 << 0 ;
    cout << "v = \n" << v.transpose() << "\n\n";
    cout << "w = \n" << w.transpose() << "\n\n";
    cout << "-v + w - v =\n" << (-v + w - v).transpose() << "\n\n";
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

