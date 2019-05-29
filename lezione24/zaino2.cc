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

typedef struct {
  integer         peso_totale;
  vector<integer> lista_pesi;
} Lista_oggetti;

/*\
 Calcolo massimo peso che uno Zaino di capacita C
 puo portare data un lista di pesi P selezionati
 dai primi k.
 E salva la lista dei pesi inseriti nello zaino.

 Soluzione ricorsiva pura

\*/

void
Zaino(
  // ingresso
  integer                 C, // capacità
  vector<integer> const & P, // lista di pesi
  integer                 k, // cerco massimo tra P[0]...P[k-1]
  // uscita
  Lista_oggetti         & lista // lista pesi inseriti nello Zaino
) {

  if ( k == 1 ) {
    // inizializzo lista in uscita;
    lista.lista_pesi.clear();
    lista.peso_totale = 0;
    if ( P[0] <= C ) {
      // un solo peso che puo essere inserito nello zaino
      // aggionamento della struttura in uscita
      lista.lista_pesi.push_back( P[0] );
      lista.peso_totale = P[0];
    }
    return;
  }

  // calcolo peso totale se non inserisco il peso P[k-1]
  Zaino( C, P, k-1, lista ); // soluzione senza inserire il peso
  if ( P[k-1] <= C ) { // posso inserirlo
    Lista_oggetti lista_temporanea;
    Zaino( C-P[k-1], P, k-1, lista_temporanea );
    // aggiungo ultimo peso alla soluzione parziale calcolata ricorsivamente
    lista_temporanea.peso_totale += P[k-1];
    lista_temporanea.lista_pesi.push_back(P[k-1]);
    // scelgo lista migliore tra le due
    bool add_weight_is_better = false;
    if ( lista.peso_totale == lista_temporanea.peso_totale ) {
      // pesi uguali, scelgo lista con piu oggetti
      // assegno direttamente il valore booleano del confronto
      add_weight_is_better = lista.lista_pesi.size() < lista_temporanea.lista_pesi.size();
    } else {
      add_weight_is_better = lista.peso_totale < lista_temporanea.peso_totale;
    }
    if ( add_weight_is_better ) {
      // copia lista migliore in uscita
      lista.peso_totale = lista_temporanea.peso_totale;
      lista.lista_pesi.resize(lista_temporanea.lista_pesi.size());
      std::copy( lista_temporanea.lista_pesi.begin(),
                 lista_temporanea.lista_pesi.end(),
                 lista.lista_pesi.begin() );
    }
  }
}

int
main() {

  vector<integer> P;

  P.clear();
  P.reserve(100);
  P.push_back(5);
  P.push_back(7);
  P.push_back(11);
  P.push_back(13);
  P.push_back(17);
  P.push_back(23);
  P.push_back(29);
  P.push_back(31);
  P.push_back(37);

  integer N = integer(P.size());
  integer C = 63;

  Lista_oggetti lista; // lista pesi inseriti nello Zaino
  Zaino( C, P, N, lista );

  cout
    << "Lo Zaino di capacita' : " << C
    << " puo' essere riempito fino a "
    << lista.peso_totale << " chili con "
    << lista.lista_pesi.size() << " oggetti\n";

  for ( integer i = 0; i < lista.lista_pesi.size(); ++i )
    cout << "Peso[ " << i << "] = " << lista.lista_pesi[i] << '\n';

  return 0;
}
