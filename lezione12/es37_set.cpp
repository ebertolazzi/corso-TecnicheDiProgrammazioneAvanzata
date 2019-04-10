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
#include <iostream>
#include <algorithm> // per std::swap
#include <string> // stringhe C++

using namespace std;


// includo liberia STL per il contenitore "vector"
#include <set>

/*
  STL = contenitori + iteratori + algoritmi
        (dato del contenitore templatizzato)
*/

//bool is_even( int i ) { return (i&1) == 0; }
bool is_even( int i ) { return (i % 2) == 0; }

int
main() {
  set<int> a; // instanzio `a` come contenitore del tipo vector
                 // con dati del tipo int

  // metodi dell'oggetto vector
  a.clear(); // inizializzo a vettore vuoto
  // a.reserve( 100 );
  // reserve non ha senso per una lista

  a.insert( 1 ); // inserisco numero 1 in coda al vettore
  a.insert( 2 ); // inserisco numero 2 in coda al vettore
  a.insert( 3 ); // inserisco numero 3 in coda al vettore
  a.insert( 4 ); // inserisco numero 4 in coda al vettore
  a.insert( 5 ); // inserisco numero 5 in coda al vettore

  // stampa "modo C++" con iteratore
  // interator       = iteratore su elementi del contenitore
  // const_interator = iteratore su elementi del contenitore
  //                   ma con "accesso read only"
  set<int>::const_iterator it = a.begin(); // iterator "punta" al primno elemento
  for ( int i = 0; it != a.end(); ++it, ++i )
    cout << "a[ " << i << "] = " << *it << '\n';

  // riempio vettore di numeri casuali
  a.clear(); // inizializzo a vettore vuoto
  // a.reserve( 100 ); non serve per le liste
  Random rnd;
  for ( int i = 0; i < 20; ++i )
    a.insert( int( rnd.dice( -100, 100 ) ) );
  cout << "CASUALE\n";
  for ( it = a.begin() ; it != a.end(); ++it )
    cout << *it << ", ";
  cout << "\n";

  // restituisce iteratore che punta a elemento massimno
  it = max_element( a.begin(), a.end() );
  cout << "MASSIMO = " << *it << "\n";

  set<int> aa, bb;
  for ( int i = 0; i < 10; ++i ) {
    aa.insert( int( rnd.dice( 0, 10 ) ) );
    bb.insert( int( rnd.dice( 0, 10 ) ) );
  }
  cout << "CASUALE\n";
  cout << "aa ";
  for ( it = aa.begin() ; it != aa.end(); ++it )
    cout << ", " << *it;
  cout << "\n";

  cout << "bb ";
  for ( it = bb.begin() ; it != bb.end(); ++it )
    cout << ", " << *it;
  cout << "\n";

  // nel caso di insiemi non ordinati (set)
  // bisogna usare std::inserter per inserire ogni volta
  // l'eleemnto della intersezione trovato
  set<int> cc;
  set_intersection( aa.begin(), aa.end(),
                    bb.begin(), bb.end(),
                    std::inserter(cc,cc.begin()) );
  cout << "cc ";
  for ( it = cc.begin() ; it != cc.end(); ++it )
    cout << ", " << *it;
  cout << "\n";

  return 0;
};
