#include <iostream>
using namespace std;

// int = intero
/*
  tipi base

  char         = carattere
  int          = intero
  unsigned int = intero senza segno
  double       = numero floating point

  ----
  float        = numero floating point
                 singola precisione
  long         = intero "grande"
  short        = intero "piccolo"

*/

int
main() {
  int a[100]; // riserva 100 elementi per il vettore a
  int n = 8;  // uso 8 elementi del vettore
  int i, idx;
  // inizializza i primi 8 elementi
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  a[3] = -1;
  a[4] = 4;
  a[5] = -9;
  a[6] = 4;
  a[7] = 0;

  // cerco minimo
  idx = 0;
  for ( i = 1; i < n; ++i )
    if ( a[i] > a[idx] )
      idx = i;

  cout
    << "a[" << idx << "] = "
    << a[idx] << " e' massimo\n";
   return 0; // esce dal programma e restiuisce 0
}
