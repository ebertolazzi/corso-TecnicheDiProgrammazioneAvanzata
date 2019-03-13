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

/*\
  Definisco struttura "sono_una_struttura"
  con 3 "campi"
  sono_un_intero
  sono_un_numero
  sono_una_stringa
\*/
//struct __attribute__((__packed__)) sono_una_struttura {
struct sono_una_struttura {
  int    sono_un_intero;
  char   sono_una_stringa[13];
  double sono_un_numero;
};

struct sono_una_struttura2 {
  int    a1;
  double b1;
  int    a2;
  double b2;
  int    a3;
  double b3;
  int    a4;
  double b4;
  int    a5;
  double b6;
};

struct sono_una_struttura3 {
  double b1;
  double b2;
  double b3;
  double b4;
  double b6;
  int    a1;
  int    a2;
  int    a3;
  int    a4;
  int    a5;
};

using namespace std;

int
main() {
  // definisco la variabile S come una stuttura
  struct sono_una_struttura S, SVEC[5];
  S.sono_un_intero = 1;
  S.sono_un_numero = 1.5;
  S.sono_una_stringa[0] = 'p';
  S.sono_una_stringa[1] = 'i';
  S.sono_una_stringa[2] = 'p';
  S.sono_una_stringa[3] = 'p';
  S.sono_una_stringa[4] = 'o';
  S.sono_una_stringa[5] = '\0';

  SVEC[0].sono_un_intero = 1;
  SVEC[0].sono_un_numero = 1.5;
  SVEC[0].sono_una_stringa[0] = 'p';
  SVEC[0].sono_una_stringa[1] = 'i';
  SVEC[0].sono_una_stringa[2] = 'p';
  SVEC[0].sono_una_stringa[3] = 'p';
  SVEC[0].sono_una_stringa[4] = 'o';
  SVEC[0].sono_una_stringa[5] = '\0';

  cout << S.sono_un_intero   << '\n';
  cout << S.sono_un_numero   << '\n';
  cout << S.sono_una_stringa << '\n';

  cout << "sizeof(S.sono_un_intero)   = " << sizeof(S.sono_un_intero) <<'\n';
  cout << "sizeof(S.sono_un_numero)   = " << sizeof(S.sono_un_numero) <<'\n';
  cout << "sizeof(S.sono_una_stringa) = " << sizeof(S.sono_una_stringa) <<'\n';
  cout << "sizeof(S)                  = " << sizeof(S) <<'\n';

  // static_cast<USCITA>(INGRESSO) trasforma INGRESSO come il tipo in USCITA
  // se lo puo fare

  // reinterpret_cast<USCITA>(INGRESSO) reinterpreta INGRESSO come il tipo in USCITA
  // senza nessun controllo

  unsigned long isono_un_intero   = reinterpret_cast<unsigned long>(&S.sono_un_intero);
  unsigned long isono_un_numero   = reinterpret_cast<unsigned long>(&S.sono_un_numero);
  unsigned long isono_una_stringa = reinterpret_cast<unsigned long>(&S.sono_una_stringa);

  unsigned long imin = std::min( isono_una_stringa, std::min( isono_un_intero, isono_un_numero ) );

  cout << "addr(S.sono_un_intero)   = " << &S.sono_un_intero   <<'\n';
  cout << "addr(S.sono_un_numero)   = " << &S.sono_un_numero   <<'\n';
  cout << "addr(S.sono_una_stringa) = " << &S.sono_una_stringa <<'\n';

  cout << "offs(S.sono_un_intero)   = " << isono_un_intero-imin   <<'\n';
  cout << "offs(S.sono_un_numero)   = " << isono_un_numero-imin   <<'\n';
  cout << "offs(S.sono_una_stringa) = " << isono_una_stringa-imin <<'\n';

  struct sono_una_struttura2 S2;
  struct sono_una_struttura3 S3;
  cout << "sizeof(S2) = " << sizeof(S2) <<'\n';
  cout << "sizeof(S3) = " << sizeof(S3) <<'\n';

  return 0;
};
