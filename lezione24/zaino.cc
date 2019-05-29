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

 Soluzione ricorsiva pura

\*/
pair<integer,integer>
Zaino(
  integer                 C, // capacità
  vector<integer> const & P, // lista di pesi
  integer                 k  // cerco massimo tra P[0]...P[k-1]
) {
  if ( k == 1 ) {
    // un solo peso da inserire
    if ( P[0] > C ) return pair<integer,integer>(0,0);
    else            return pair<integer,integer>(1,P[0]);
  }

  // calcolo peso totale se non inserisco il peso P[k-1]
  pair<integer,integer> peso = Zaino( C, P, k-1 );
  if ( P[k-1] < C ) { // posso inserirlo
    pair<integer,integer> peso_si = Zaino( C-P[k-1], P, k-1 );
    // inserisco peso nello zaino
    ++peso_si.first; // incremento contatore oggetti
    peso_si.second += P[k-1]; // aggiungo peso al totale calcolato
    if ( (peso_si.second == peso.second && peso_si.first > peso.first ) ||
         peso_si.second > peso.second ) peso = peso_si; // conviene inerire in peso
  }
  return peso;
}


int
main() {

  vector<integer> P;

  P.clear();
  P.reserve(100);
  P.push_back(12);
  P.push_back(12);
  P.push_back(32);
  P.push_back(22);
  P.push_back(32);
  P.push_back(14);
  P.push_back(78);
  P.push_back(20);
  P.push_back(12);
  P.push_back(18);
  P.push_back(18);
  P.push_back(12);
  P.push_back(82);
  P.push_back(92);

  integer N = integer(P.size());

  integer C = 157;
  pair<integer,integer> peso = Zaino( C, P, N );

  cout
    << "Lo Zaino di capacita' : " << C
    << " puo' essere riempito fino a "
    << peso.second << " chili con "
    << peso.first << " oggetti\n";

  return 0;
}
