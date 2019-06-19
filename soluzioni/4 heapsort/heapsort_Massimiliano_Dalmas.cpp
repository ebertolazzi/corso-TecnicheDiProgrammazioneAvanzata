#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "course_lib.h"

using namespace std;

#define DIST(ptr1,ptr2)      ((ptr2) - (ptr1))
#define DOUBLE_PTR(ptr)      (base + (DIST(base,ptr)      << 1))
#define LEFT(ptr)            (DOUBLE_PTR(ptr) + 1)
#define SHIFT(a,b)           (*(a) = *(b))

#define WRITE_VECTOR(v,output,vmax)       \
do{                                       \
    for (auto tmp = v;tmp <= vmax;tmp++)  \
      output << *tmp << " ";              \
    output << "\n";                       \
} while(0)


int
main(void) {

  ifstream fin("input.txt");
  ofstream fout("output.txt");

  // legge dimensione vettore da file
  int n;
  fin >> n;
  int * vec;

  // allocazione dinamica
  AutoAllocate<int> A1( n, &vec );

  // legge vettore da file
  for ( int i=0; i<n; ++i ) fin >> vec[i];
  fin.close(); // chiude file (non piu necessario)

  int *max, *parent, *base;
  int val;
  base   = vec;
  max    = base + n;
  parent = base + (n >> 1);
  bool p = 0;
  while (1)
  {
    if (parent > base)
      val = *(--parent);
    else
    {

      max--;
      if (!p)
      {
        WRITE_VECTOR(vec,fout,max);
        p = 1;
      }
      if (max == base)
          break;
      val = *max;
      SHIFT(max,base);
    }

    auto index = parent;
    auto child = LEFT(index);

    while (child < max)
    {
      if (((child + 1) < max) && (*(child + 1) > *child))
        child++;
      if (*child > val)
      {
        SHIFT(index,child);
        index = child;
        child = LEFT(child);
      } else
        break;
    }
    SHIFT(index,&val);
  }

  // salva vettore
  for ( int i=0; i<n; ++i ) fout << vec[i] << " ";
  fout << '\n';

  // chiude file con i risultati
  fout.close();
  return 0;
}
