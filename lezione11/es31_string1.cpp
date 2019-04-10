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
#include <string.h> // stringhe C

using namespace std;

class String {
private:
  char * data; // puntatore alla stringa allocata in memoria
public:
  // costruttore di default
  String()
  : data(nullptr) // chiamo costruttore di data = nullptr
  { cout << "costruttore 1\n"; /* niente da fare */ }

/* Forme alternative
  String()
  { data = nullptr; }

  String()
  { this->data = nullptr; }
*/

/*
  String( char const * in ) {
    int len = strlen(in); // libreria C in <string.h>
    data = new char[ len+1 ]; // lunghezza + charattere fine stringa
    strcpy( data, in );
  }
*/
  String( char const * in )
  : data( (char *)(in) )
  {
    cout << "costruttore 2\n";
  }

  ~String() {
    cout << "distruttore addr data: " << &this->data << "\n";
    cout << "data point to: " << this->data << "\n";
    // dealloco solo se data era stato allocato
    if ( this->data != nullptr ) delete [] this->data;
    this->data = nullptr;
  }
};

int
main() {
  char * t1 = new char[100];
  strcpy( t1, "pippo" );
  String s1(t1);
  String s2(t1);
  return 0;
};
