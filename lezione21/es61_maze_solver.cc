/*\

\*/

#include <vector>
#include <deque>
#include <utility> // per pair

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
  maze[i][j] = 5; // marcata root

  deque<pair<int,int> > fronte;

  // cerco vicini e aggiungo a lista del fronte e si scrive
  // nel maze[i][j] corrispondente la direzione della root

  ...

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
  while ( ... ) {


  }

  std::reverse( soluzione.begin(), soluzione.end() );

}

