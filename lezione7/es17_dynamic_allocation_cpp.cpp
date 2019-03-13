/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
:|:
\*/

#include "course_lib.h"

using namespace std;

int
main() {

  /* allocazione, alla C++ */
  /*\

    puntatore = new TIPO;    (per allocasre un singolo oggetto/tipo)
    puntatore = new TIPO[N]; (per allocasre un singolo oggetto/tipo)

    puntatore = variabile che conterrà indirizzo del blocco di memoria allocato

    delete    puntatore (se allocato come new TIPO);
    delete [] puntatore (se allocato come new TIPO[N] );

  \*/

  int * int_pointer;
  int_pointer = new int[10]; // alloca 10 interi
  // sizeof(int) = numero di byte che usa un int

  float * float_pointer;
  float_pointer = new float[10]; // alloca 10 float

  double * double_pointer;
  double_pointer = new double[5]; // alloca 5 double
  // sizeof(int) = numero di byte che usa un int

  struct pippo {
    double e1, e2, e3, e4, e5;
  };

  struct pippo * ptr_pippo;

  ptr_pippo = new (struct pippo);

  // sizeof(int) = numero di byte che usa un int

  // 0xNUMERO = prefisso per indicare un numero esadecimale
  // 0NUMERO  = prefisso per indicare un numero OTTALE
  // 077 = 111111 binario = 0x3F
  cout
    << "indirizzo puntato da int_pointer = "
    << int_pointer << '\n'
    << "indirizzo puntato da float_pointer = "
    << float_pointer << '\n'
    << "indirizzo puntato da double_pointer = "
    << double_pointer << '\n'
    << "indirizzo puntato da ptr_pippo = "
    << ptr_pippo << '\n';

  cout << "Byte usati da int_pointer    = " << 10*sizeof(int) << '\n' ;
  cout << "Byte usati da float_pointer  = " << 10*sizeof(float) << '\n' ;
  cout << "Byte usati da double_pointer = " << 5*sizeof(double) << '\n' ;
  cout << "Byte usati da ptr_pippo      = " << sizeof(struct pippo) << '\n' ;

  cout
    << "differenza indirizzi = "
    << (char*)float_pointer-(char*)int_pointer << '\n';
  cout
    << "differenza indirizzi = "
    << (char*)double_pointer-(char*)float_pointer << '\n';
  cout
    << "differenza indirizzi = "
    << (char*)ptr_pippo-(char*)double_pointer << '\n';

  int_pointer[0] = 123;
  int_pointer[4] = 23;
  for ( int i = 0; i < 10; ++i )
    cout << "int_pointer[" << i << "] = " << int_pointer[i] << '\n';

   // stampo 8 byte precedenti dei puntatori
   for ( int i = 8; i > 0; --i )
     cout << "int_pointer[-" << i << "] = "
          << (int)( ((char*) int_pointer)[-i] ) << '\n';
   for ( int i = 8; i > 0; --i )
     cout << "float_pointer[-" << i << "] = "
          << (int)( ((char*) float_pointer)[-i] ) << '\n';
   for ( int i = 8; i > 0; --i )
     cout << "double_pointer[-" << i << "] = "
          << (int)( ((char*) double_pointer)[-i] ) << '\n';

  delete [] int_pointer;
  delete [] float_pointer;
  delete [] double_pointer;
  delete [] ptr_pippo;

  return 0;
};
