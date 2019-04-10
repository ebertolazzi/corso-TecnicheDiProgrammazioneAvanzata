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

/*
  Excursus sulle STL

  std::vector;

  namespace std {
    // contenitore della libreria standard
  }


  namespace std {
    // aggiungo cose ....

    double pippo( double x ) {
      return x+1;
    }
  }

  Per accedere a pippo devo usare il nome della "scatola" std
  e l'operatore di scopo

  double res = std::pippo( 10 );

  Si posso "estrarre" oggetti dalla scatola 1 a 1

  using std::pippo;

  double res = pippo( 10 );

  Oppure si può "svuotare" tutta la scatola...

  using namespace std;


*/

// includo liberia STL per il contenitore "vector"
#include <vector>

/*
  STL = contenitori + iteratori + algoritmi
        (dato del contenitore templatizzato)
*/

//bool is_even( int i ) { return (i&1) == 0; }
bool is_even( int i ) { return (i % 2) == 0; }

int
main() {
  vector<int> a; // instanzio `a` come contenitore del tipo vector
                 // con dati del tipo int

  // metodi dell'oggetto vector
  a.clear(); // inizializzo a vettore vuoto
  a.reserve( 100 ); // il vettore rimane vuoto ma "prealloco" almeno 100
                    // elementi per futuri inserimenti

  a.push_back( 1 ); // inserisco numero 1 in coda al vettore
  a.push_back( 2 ); // inserisco numero 2 in coda al vettore
  a.push_back( 3 ); // inserisco numero 3 in coda al vettore
  a.push_back( 4 ); // inserisco numero 4 in coda al vettore
  a.push_back( 5 ); // inserisco numero 5 in coda al vettore

  a.resize( 4 ); // ridimensiona il vettore (puo essere "allargato" o "ristretto")

  // stampa "modo C"
  for ( int i = 0; i < a.size(); ++i )
    cout << "a[ " << i << "] = " << a[i] << '\n';

  // stampa "modo C" con puntatore
  int const * ptr     = &a[0];
  int const * ptr_end = ptr + a.size(); // 1 oltre ultimo elemento
  for ( int i = 0; ptr < ptr_end; ++ptr, ++i )
    cout << "a[ " << i << "] = " << *ptr << '\n';

  // stampa "modo C++" con iteratore
  // interator       = iteratore su elementi del contenitore
  // const_interator = iteratore su elementi del contenitore
  //                   ma con "accesso read only"
  vector<int>::const_iterator it = a.begin(); // iterator "punta" al primno elemento
  for ( int i = 0; it != a.end(); ++it, ++i )
    cout << "a[ " << i << "] = " << *it << '\n';

  it = a.begin(); // iterator "punta" al primno elemento
  for ( ; it != a.end(); ++it )
    cout << "a[ " << (it-a.begin()) << "] = " << *it << '\n';
    //                    ^^^^
    // la differenza tra due iteratori da la loro "distanza"
    // come numero intero

  // riempio vettore di numeri casuali
  a.clear(); // inizializzo a vettore vuoto
  a.reserve( 100 ); // il vettore rimane vuoto ma "prealloco" almeno 100
  Random rnd;
  for ( int i = 0; i < 20; ++i )
    a.push_back( int( rnd.dice( -100, 100 ) ) );
  cout << "CASUALE\n";
  for ( it = a.begin() ; it != a.end(); ++it )
    cout << "a[ " << (it-a.begin()) << "] = " << *it << '\n';

  // restituisce iteratore che punta a elemento massimno
  it = max_element( a.begin(), a.end() );
  cout << "MASSIMO = " << *it << "\n";

  // algoritmi a disposizione
  // sort
  sort( a.begin(), a.end() );
  cout << "ORDINATO\n";
  for ( it = a.begin() ; it != a.end(); ++it )
    cout << "a[ " << (it-a.begin()) << "] = " << *it << '\n';

  // eliminazione elementi il cui valore è pari
  //a.erase(remove_if( a.begin(), a.end(), is_even ));
  //a.erase(remove_if( a.begin(), a.end(),
  //                   [&](int const &p) { return (p % 2) == 0; }), a.end());

  //for ( it = a.begin() ; it != a.end(); ++it )
  //  if ( (*it % 2) == 0 ) it = a.erase( it );

  //cout << "ELIMINATI PARI\n";
  //for ( it = a.begin() ; it != a.end(); ++it )
  //  cout << "a[ " << (it-a.begin()) << "] = " << *it << '\n';

  vector<int> aa, bb, cc;
  for ( int i = 0; i < 10; ++i ) {
    aa.push_back( int( rnd.dice( 0, 10 ) ) );
    bb.push_back( int( rnd.dice( 0, 10 ) ) );
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

  std::sort(aa.begin(), aa.end());
  std::sort(bb.begin(), bb.end());
  set_intersection( aa.begin(), aa.end(),
                    bb.begin(), bb.end(),
                    back_inserter(cc) );
  cout << "cc ";
  for ( it = cc.begin() ; it != cc.end(); ++it )
    cout << ", " << *it;
  cout << "\n";

  return 0;
};
