#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

/*

Connected
Path:
1
6
11
10
18
tiles.pdf

*/

using namespace std;

typedef struct {
  double xmin, xmax;
  double ymin, ymax;
  double x() const { return (xmin+xmax)/2; }
  double y() const { return (ymin+ymax)/2; }
} tile;

typedef struct {
  double x, y;
} point;

static
bool
doOverlap( tile const & A, tile const & B ) {
  // If one rectangle is on left side of other
  if (A.xmin > B.xmax || B.xmin > A.xmax) return false;
  // If one rectangle is above other
  if (A.ymin > B.ymax || B.ymin > A.ymax) return false;
  return true;
}

static
bool
doOverlap( tile const & A, point const & pt ) {
  // If the point is on left/right side of the tile
  if (A.xmin > pt.x || pt.x > A.xmax) return false;
  // If the point is above/below the tile
  if (A.ymin > pt.y || pt.y > A.ymax) return false;
  return true;
}

bool
connected(
  vector<tile> const & board,
  double x0, double y0,
  double x1, double y1,
  vector<int> & path
) {
  point p0 = {x0, y0};
  point p1 = {x1, y1};

  // cerca la piastrella di partenza e di arrivo
  // se i punti cascano fuori dalla piastrella non c'è connessione
  int i0, i1;
  i0 = i1 = -1;
  bool found = false;
  for ( int i = 0; !found && i < board.size(); ++i ) {
    if ( i0 == -1 && doOverlap( board[i], p0 ) ) i0 = i;
    if ( i1 == -1 && doOverlap( board[i], p1 ) ) i1 = i;
    if (i0>=0 && i1>=0) found = true;
  }

  // uno o piu punti non sulle piastrelle
  if (!found) {
    cerr << "Not found" << endl;
    return false;
  }

  // costruisco grafo come matrice di adiacenza
  vector<vector<int> > adj(board.size());
  for ( int i = 0; i < board.size(); ++i ) {
    for ( int j = i; j < board.size(); ++j ) {
      if (doOverlap( board[i], board[j] )) {
        adj[i].push_back(j);
        adj[j].push_back(i);
      }
    }
  }

  // avanzamento dello spanning treee
  vector<bool> visited(board.size(), false);
  vector<int>  parent(board.size(), -1);
  queue<int>   toExplore;
  toExplore.push(i0);
  visited[i0] = true;
  found = false;
  while (!toExplore.empty()) {
    // prossima piastrella (nodo) da esplorare
    int currTile = toExplore.front();
    toExplore.pop();
    if ( currTile == i1 ) { found = true; break; }

    for ( int i = 0; i < adj[currTile].size(); ++i ) {
      if ( !visited[adj[currTile][i]] ) {
        // prende primi vicini non ancora visitati
        toExplore.push( adj[currTile][i] );
        visited[ adj[currTile][i] ] = true;     // marca nodo come visitato
        parent[  adj[currTile][i] ] = currTile; // salva padre
      }
    }
  }

  if ( found ) {
    // prende a ritroso la path dal nodo di arrivo al nodo di partenza
    path.clear();
    int currTile = i1;
    while ( currTile != -1 ) {
      path.push_back( currTile );
      currTile = parent[ currTile ];
    }
    reverse( path.begin(), path.end() );
  }

  return found;
}
