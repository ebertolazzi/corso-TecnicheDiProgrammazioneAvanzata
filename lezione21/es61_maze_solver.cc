/*\

\*/

#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include <utility> // per pair

using namespace std;

static
void
read_maze(
  char const               fname[],
  unsigned               & nrow,
  unsigned               & ncol,
  vector<vector<int> >   & maze,
  vector<pair<int,int> > & ingresso,
  vector<pair<int,int> > & uscita
) {
  // inizializzo labirinto
  maze.clear();
  vector<string> rows;

  // leggo labirinto e motto in vettore di stringhe
  ifstream file(fname);
  while ( file.good() ) {
    string line;
    getline( file, line, '\n');
    if ( line.size() > 0 ) rows.push_back(line);
  }
  file.close();
  nrow = unsigned( rows.size() );
  ncol = unsigned( rows[0].size() );
  cout << "nrow = " << nrow << " ncol = " << ncol << '\n';

  maze.resize(nrow);
  for ( unsigned i = 0; i < nrow; ++i ) {
    maze[i].resize(ncol);
    std::fill( maze[i].begin(), maze[i].end(), -1); // riempio con muro
    for ( unsigned j = 0; j < ncol; ++j ) {
      char c = rows[i][j];
      if ( c == ' ' || c == 'I' || c == 'U' ) {
        maze[i][j] = 0; // cella libera
        if ( c == 'I' ) ingresso.push_back( pair<int,int>( i,j) ) ;
        if ( c == 'U' ) uscita.push_back( pair<int,int>( i,j) ) ;
      }
    }
  }
}

/*

maze è matrice (vettore di vettori) con allocato un labirinto

per accedere all'elemento i,j

maze[i][j]

maze[i][j] < 0 per celle "muro"
maze[i][j] = 0 per celle "libere"

dir = 1, 2, 3, 4 direzioni di movimento

1 = sinistra
2 = destra
3 = sopra
4 = sotto
5 = nessuna direzione, nodo di root

SCOPO: costruire in modo implicito lo spanning tree

maze[i][j] = direzione dove sta il padre

nel caso di root la direzione è 5

*/

void
maze_spanning_tree(
  vector<vector<int> > & maze,
  pair<int,int>  const & root
) {
  /*
   Inizializzazione
  \*/

  // marco root
  int iroot = root.first;
  int jroot = root.second;

  maze[iroot][jroot] = 5; // marcata root

  deque<pair<int,int> > fronte;

  // cerco vicini e aggiungo a lista del fronte e si scrive
  // nel maze[i][j] corrispondente la direzione della root

  while ( ! fronte.empty() ) {
    pair<int,int> ij = fronte.back(); fronte.pop_back();

    // cerco vicini e aggiungo a lista del fronte e si scrive
    // nel maze[i][j] corrispondente la direzione del nodo ij

  }


}

void
maze_solve(
  vector<vector<int> >   & maze,
  pair<int,int>  const   & ingresso,
  pair<int,int>  const   & uscita,
  vector<pair<int,int> > & soluzione
) {
  maze_spanning_tree( maze, ingresso );

  soluzione.clear();
  // a partire da uscita riempio soluzione
  soluzione.push_back(uscita);
  while ( true ) {


  }
  std::reverse( soluzione.begin(), soluzione.end() );
}

int
main() {

  try {
    // leggo labirinto
    unsigned nrow, ncol;
    vector<vector<int> >   maze;
    vector<pair<int,int> > ingresso;
    vector<pair<int,int> > uscita;
    vector<pair<int,int> > soluzione;

    read_maze( "maze1.txt", nrow, ncol, maze, ingresso, uscita );
    maze_solve( maze, ingresso.front(), uscita.front(), soluzione );

    // stampa soluzione

  }
  catch ( string const & error ) {
    cerr << "Errore: " << error << "\n\n";
  }
  catch ( exception const & error ) {
    cerr << "Exception: " << error.what() << "\n\n";
  }
  catch ( ... ) {
    cerr << "Exception found: Unknown error\n"  ;
  }
  cout << "END OF PROGRAM\n" ;

  return 0 ;
}
