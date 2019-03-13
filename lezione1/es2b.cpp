#include <iostream>
using namespace std;

int
main() {
  // riserva 100 elementi per il vettore a
  // e iniializz ai primi 8 elementi
  int a[100] = {1,2,3,-1,4,-9,4, 0};
  int n = 8;  // uso 8 elementi del vettore
  int i, idx;

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
