/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi e prof. Andrea Del Prete
:|:
:|:
\*/

#include "course_lib.h"
#include <iostream>
#include <iomanip> // per setw
#include <algorithm> // per std::swap

using namespace std;

int
main( int argc, char * argv[] ) {
  // stringhe alla C (vettore di caratteri)
  int const N = 100;
  char stringa[N]; // riservo 100 caratteri alla stringa
  /*\
    stringa_con_inizializzazione = puntatore di memoria
    Il puntatore è inizializzato all'indirizzo
    del blocco di memoria che contiene una copia
    della stringa costante "pippo"
  \*/
  char const * puntatore_a_blocco_di_caratteri  = "pippo";
  char const * puntatore_a_blocco_di_caratteri2 = "pluto";
  static char stringa_con_inizializzazione[]    = "pippo" ;

  stringa_con_inizializzazione[0] = 'q';
  // la istruzione seguente non si può fare
  // puntatore_a_blocco_di_caratteri[0] = 'r';

  cout
    << "stringa_con_inizializzazione = "
    << stringa_con_inizializzazione << '\n';

  cout
    << "indirizzo puntatore_a_blocco_di_caratteri = "
    << (unsigned long)puntatore_a_blocco_di_caratteri
    << '\n';

  cout
    << "indirizzo puntatore_a_blocco_di_caratteri2 = "
    << (unsigned long)puntatore_a_blocco_di_caratteri2
    << '\n';

  cout
    << "indirizzo stringa_con_inizializzazione = "
    << (unsigned long)stringa_con_inizializzazione
    << '\n';

  cout
    << "puntatore_a_blocco_di_caratteri = "
    << puntatore_a_blocco_di_caratteri << '\n';
  return 0;
};
