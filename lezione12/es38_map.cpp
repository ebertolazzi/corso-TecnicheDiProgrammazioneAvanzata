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


// includo liberia STL per il contenitore "vector"
#include <map>

using namespace std;

/*
  STL = contenitori + iteratori + algoritmi
        (dato del contenitore templatizzato)
*/

//bool is_even( int i ) { return (i&1) == 0; }
bool is_even( int i ) { return (i % 2) == 0; }

int
main() {
  map<string,int> eta; // instanzio `a` come contenitore del tipo vector
                       // con dati del tipo int

  eta["pippo"]    = 121;
  eta["pluto"]    = 111;
  eta["paperino"] = 23;

  map<string,int>::const_iterator it;
  for ( it = eta.begin(); it != eta.end(); ++it )
    cout << "chiave = " << (*it).first << " valore = " << it->second << '\n';

  //map<string,vector<int> > eta; // instanzio `a` come contenitore del tipo vector

  return 0;
};
