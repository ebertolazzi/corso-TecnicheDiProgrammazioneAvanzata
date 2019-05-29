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


// copia un vettore di interi su un
static
inline
void
copy_vec(
  vector<integer> const & from,
  vector<integer>       & to
) {
  to.resize( from.size() );
  std::copy( from.begin(), from.end(), to.begin() );
}

/*\
 Calcolo massimo peso che uno Zaino di capacita C
 puo portare data un lista di pesi P selezionati
 dai primi k.
 E salva la lista dei pesi inseriti nello zaino.

 Soluzione con programmazione dinamica

\*/

/*
 Z[k][C] = lista, calcolata con Zaino( C, P, k, lista)
*/

void
Zaino_ProgrammazioneDinamica(
  // ingresso
  integer                 C, // capacità
  vector<integer> const & P, // lista di pesi
  // uscita
  Lista_oggetti         & lista // lista pesi inseriti nello Zaino
) {
  // allocazione della matrice per dei possibili casi
  vector<vector<Lista_oggetti> > mat;
  integer nr = P.size();
  integer nc = C+1;
  mat.resize(nr);
  for ( integer i = 0; i < nr; ++i ) mat[i].resize( nc );
  // inizializzazione casi triviali, capacita 0
  for ( integer i = 0; i < nr; ++i ) {
    Lista_oggetti & mi0 = mat[i][0]; // alias di mat[i][0]
    mi0.peso_totale = 0;
    mi0.lista_pesi.clear();
  }
  // inizializzazione casi triviali, 1 peso ebbasta
  for ( integer jC = 1; jC < nc; ++jC ) {
    Lista_oggetti & m0j = mat[0][jC]; // alias di mat[0][j]
    if ( P[0] <= jC ) {
      m0j.peso_totale = P[0];
      m0j.lista_pesi.clear();
      m0j.lista_pesi.push_back(P[0]);
    } else {
      m0j.peso_totale = 0;
      m0j.lista_pesi.clear();
    }
  }
  // riempimento della matrice usando "la ricorsione" per calcolare i valori
  for ( integer i = 1; i < nr; ++i ) {
    for ( integer jC = 1; jC < nc; ++jC ) {
      Lista_oggetti & mij = mat[i][jC]; // elemento da inserire
      // calcolo peso totale se non inserisco il peso P[k-1]
      Lista_oggetti const & msopra = mat[i-1][jC]; // soluzione senza inserire il peso
      // copio come candidato per la soluzione
      mij.peso_totale = msopra.peso_totale;
      copy_vec( msopra.lista_pesi, mij.lista_pesi );

      if ( P[i] <= jC ) { // posso inserirlo
        Lista_oggetti const & msinistra = mat[i-1][jC-P[i]];
        // aggiungo ultimo peso alla soluzione parziale calcolata ricorsivamente
        Lista_oggetti temp;
        temp.peso_totale = msinistra.peso_totale + P[i];
        copy_vec( msinistra.lista_pesi, temp.lista_pesi );
        temp.lista_pesi.push_back(P[i]);

        // scelgo lista migliore tra le due
        bool add_weight_is_better = false;
        if ( mij.peso_totale == temp.peso_totale ) {
          // pesi uguali, scelgo lista con piu oggetti
          // assegno direttamente il valore booleano del confronto
          add_weight_is_better = mij.lista_pesi.size() < temp.lista_pesi.size();
        } else {
          add_weight_is_better = mij.peso_totale < temp.peso_totale;
        }
        // se migliore aggiorno mij
        if ( add_weight_is_better ) {
          mij.peso_totale = temp.peso_totale;
          copy_vec( temp.lista_pesi, mij.lista_pesi );
        }
      }
    }
  }

  Lista_oggetti & SOL = mat.back().back();
  lista.peso_totale = SOL.peso_totale;
  copy_vec( SOL.lista_pesi, lista.lista_pesi );
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
  integer C = 64;

  Lista_oggetti lista; // lista pesi inseriti nello Zaino
  Zaino_ProgrammazioneDinamica( C, P, lista );

  cout
    << "Lo Zaino di capacita' : " << C
    << " puo' essere riempito fino a "
    << lista.peso_totale << " chili con "
    << lista.lista_pesi.size() << " oggetti\n";

  for ( integer i = 0; i < lista.lista_pesi.size(); ++i )
    cout << "Peso[ " << i << "] = " << lista.lista_pesi[i] << '\n';

  return 0;
}
