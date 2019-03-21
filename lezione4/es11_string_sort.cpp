/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
:|:
:|:
\*/

#include "course_lib.h"
#include <iostream>
#include <algorithm> // per std::swap

#include <string.h> // per prototipo strcmp

using namespace std;

/*\
:|: Ordinamento mergesort, vedi note online
:|: per la descrizione
\*/

template <> // specializzo la funzione per il tipo "char const *"
bool
compare_gt( char const * const & a, char const * const & b ) {
  // T = char const *
  return strcmp( a, b ) > 0; // a > b ?
}

int
main() {
  TicToc tm;

  int n = 10;
  /* definisco vstr vettore di 10 elementi
     ogni elemento è un puntatore a tipo carattere
     il puntatore punta ad una zona di memoria
     NON modificabile */
  char const * vstr[10];

  // la stringa "pippo" è un puntatore alla memoria
  // di un tipo carattere NON modificabile.
  // "pippo" = [ 'p', 'i', 'p', 'p', 'o', '\0' ]
  // cosiste di 6 caratteri, l'ultimo è il carattere
  // ascii 0, ovvero fine stringa.

  vstr[0] = "pippo";
  vstr[1] = "pluto";
  vstr[2] = "paperino";
  vstr[3] = "nonna papera";
  vstr[4] = "daredevil";
  vstr[5] = "hulk";
  vstr[6] = "spiderman";
  vstr[7] = "wonder woman";
  vstr[8] = "capitan america";
  vstr[9] = "iron man";

  for ( int i=0; i < n; ++i )
    cout
     << "addess of vstr[" << i << "] = `"
     << (unsigned long) vstr[i]
     << "`\n";

  tm.tic();
  bubble_sort( vstr, n );
  tm.toc();

  for ( int i=0; i < n; ++i )
    cout
     << "addess of vstr[" << i << "] = `"
     << (unsigned long) vstr[i]
     << "`\n";

  bool ok = check_if_sorted( vstr, n );
  if ( ok ) cout << "Ordinamento corretto!\n";
  else      cout << "Ordinamento fallito!\n";

  cout << "Elapsed = " << tm.elapsed_ms() << "(ms)\n";

  for ( int i=0; i < n; ++i )
    cout << "vstr[" << i << "] = `" << vstr[i] << "`\n";

  return 0;
};
