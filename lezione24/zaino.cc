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

#include <iostream>
#include <vector>

using namespace std;

typedef int integer;

/*\
 Calcolo massimo peso che uno Zaino di capacita C
 puo portare data un lista di pesi P selezionati
 dai primi k.

\*/
integer
Zaino(
  integer                 C, // capacità
  vector<integer> const & P, // lista di pesi
  integer                 k  // cerco massimo tra P[0]...P[k-1]
) {
  return 0;
}


int
main() {

  vector<integer> P;

  P.clear();
  P.reserve(100);
  P.push_back(12);
  P.push_back(2);
  P.push_back(6);
  P.push_back(5);
  P.push_back(3);
  P.push_back(1);
  P.push_back(7);
  P.push_back(2);
  P.push_back(4);
  P.push_back(8);
  P.push_back(9);
  P.push_back(11);
  P.push_back(8);
  P.push_back(9);

  integer N = integer(P.size());

  integer C = 56;
  integer peso = Zaino( C, P, N );

  cout
    << "Lo Zaino di capacita' : " << C
    << " puo' essere riempito fino a "
    << peso << " chili\n";

  return 0;
}
