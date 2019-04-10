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

  String( char const * in ) {
    int len = strlen(in); // libreria C in <string.h>
    this->data = new char[ len+1 ]; // lunghezza + charattere fine stringa
    strcpy( this->data, in );
  }

  String( String const & S ) {
    // deep copy
    int len = strlen(S.data); // libreria C in <string.h>
    this->data = new char[ len+1 ]; // lunghezza + charattere fine stringa
    strcpy( this->data, S.data );
  }

  ~String() {
    //cout << "distruttore addr data: " << &this->data << "\n";
    //cout << "data point to: " << (unsigned long)this->data << "\n";
    // dealloco solo se data era stato allocato
    if ( this->data != nullptr ) delete [] this->data;
    this->data = nullptr;
  }

  // ridefinisco A = B
  String const & operator = ( String const & S ) {
  // --- A ---                  --- B ---
    // deep copy
    int len = strlen(S.data); // libreria C in <string.h>
    this->data = new char[ len+1 ]; // lunghezza + charattere fine stringa
    strcpy( this->data, S.data );
    return *this;
  }

  String const & operator += ( String const & S );

  String const &
  operator += ( char const s[] ) {
    int len  = strlen( this->data );
    int lens = strlen( s );
    // alloco nuovo spazio di memoria per la stringa concatenata
    char * tmp = new char[ len + lens + 1];
    strcpy( tmp, this->data );
    strcpy( tmp+len, s );
    // cancella memoria puntata da data ( non piu necessaria )
    delete [] this->data;
    this->data = tmp;
    return *this;
  }

  // metodo che consente accesso a puntatore data
  // ma non permette di modificate la classe
  // ne il contenuto di quello a cui punta.
  char const *
  get_data() const
  { return this->data; }

};

String operator + ( String const & A, String const & B );
String operator + ( String const & A, char const cstr[] );

ostream &
operator << ( ostream & oggetto_stream, String const & A ) {
  // oggetto_stream == tipo cout
  oggetto_stream << A.get_data();
  return oggetto_stream;
}

int
main() {
  char * t1 = new char[100];
  strcpy( t1, "pippo" );
  String s1(t1);
  String s2(t1);
  String s3 = s1; // String s3(s1);

  s3 = s1; // chiama operatore di copia

  s3 += " pluto";
  s3 += " paperino";

  cout << s3 << '\n';
  return 0;
};
