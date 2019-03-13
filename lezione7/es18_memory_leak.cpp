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

  /*\
     esempio memory leak
  \*/

  int * int_pointer;
  int_pointer = new int[10]; // alloca 10 interi
  cout
    << "indirizzo puntato da int_pointer = "
    << int_pointer << '\n';

  // int_pointer "vecchio" è perso, non c'è modo di liberare la memoria

  int_pointer = new int[100]; // alloca 10 interi
  cout
    << "indirizzo puntato da int_pointer = "
    << int_pointer << '\n';

  delete [] int_pointer;

  return 0;
};
