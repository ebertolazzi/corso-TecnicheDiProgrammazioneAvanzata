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

typedef struct {
  char * data; // puntatore alla stringa allocata in memoria
  int    cnt;
  // cnt = contatore di quanti usano il pointer,
  //       quando cnt = 0, la memoria va distrutta
} char_shared_pointer;

class String {
private:
  char_shared_pointer * sp; // puntatore alla stringa allocata in memoria

public:
  // costruttore di default
  String()
  : sp(nullptr)
  {
  }

  String( char const * in ) {
    sp = new char_shared_pointer;
    int len = strlen(in); // libreria C in <string.h>
    this->sp->data = new char[ len+1 ]; // lunghezza + charattere fine stringa
    strcpy( this->sp->data, in );
    this->sp->cnt = 1;
  }

  String( String const & S ) {
    // shallow copy
    this->sp = S.sp;
    this->sp->cnt++; // nuova copia, incremento di 1 il contatore
  }

  ~String() {
    // decremento contatore d'uso
    this->sp->cnt--;
    // se contatore == 0 devo liberare la memorioa allocata
    if ( this->sp->cnt == 0 ) {
      if ( this->sp->data != nullptr ) delete [] this->sp->data;
      this->sp->data = nullptr;
      delete sp;
    }
  }

  // ridefinisco A = B
  String const & operator = ( String const & S ) {
  // --- A ---                  --- B ---
    // deep copy
    int len = strlen(S.sp->data); // libreria C in <string.h>
    this->sp->data = new char[ len+1 ]; // lunghezza + charattere fine stringa
    strcpy( this->sp->data, S.sp->data );
    return *this;
  }

  // metodo che consente accesso a puntatore data
  // ma non permette di modificate la classe
  // ne il contenuto di quello a cui punta.
  char const *
  get_data() const
  { return this->sp->data; }

};

int
main() {
  char * t1 = new char[100];
  strcpy( t1, "pippo" );
  String s1(t1);
  String s2(t1);
  String s3 = s1; // String s3(s1);

  s3 = s1; // chiama operatore di copia
  return 0;
};
