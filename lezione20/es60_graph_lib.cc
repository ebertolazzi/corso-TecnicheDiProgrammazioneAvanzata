/*\

\*/

#include "graph_lib.hh"
#include <fstream>
#include <sstream>

using namespace std;

static
void
read_maze(
  char const                fname[],
  unsigned                & nrow,
  unsigned                & ncol,
  unsigned                & nvertex,
  vector<vector<int> >    & vertex_pos,
  vector<vector<string> > & vertex_label
) {
  vertex_pos.clear();
  vertex_label.clear();

  // leggo labirinto e motto in vettore di stringhe
  ifstream file(fname);
  vector<string> rows;
  while ( file.good() ) {
    string line;
    getline( file, line, '\n');
    if ( line.size() > 0 ) {
      rows.push_back(line);
    }
  }
  file.close();
  nrow = unsigned( rows.size() );
  ncol = unsigned( rows[0].size() );
  cout << "nrow = " << nrow << " ncol = " << ncol << '\n';

  vertex_pos.resize(nrow);
  vertex_label.resize(nrow);

  // numero vertici
  nvertex = 0;
  for ( unsigned i = 0; i < nrow; ++i ) {
    vertex_pos[i].resize(ncol);
    vertex_label[i].resize(ncol);
    std::fill( vertex_pos[i].begin(), vertex_pos[i].end(), -1 ); // muro
    for ( unsigned j = 0; j < ncol; ++j ) {
      char c = rows[i][j];
      if ( c == ' ' || c == 'I' || c == 'U' ) {
        // posizione libera, aggiungo vertice al grafo
        vertex_pos[i][j] = nvertex++;
        // label del vertice "i,j" come stringa
        if ( c == ' ' ) {
          ostringstream oss;
          oss << i << "," << j;
          vertex_label[i][j] = oss.str();
        } else {
          vertex_label[i][j] = c;
        }
      }
    }
  }

}

static
void
build_graph(
  unsigned                        nrow,
  unsigned                        ncol,
  unsigned                        nvertex,
  vector<vector<int> >    const & vertex_pos,
  vector<vector<string> > const & vertex_label,
  GraphLib::Graph               & G
) {
  // so quanti sono i vertici, alloco memoria corrispondente
  G.resize_vertex( nvertex );
  // costruisco grafo
  for ( unsigned i = 0; i < nrow; ++i ) {
    for ( unsigned j = 0; j < ncol; ++j ) {
      int vij = vertex_pos[i][j];
      if ( vij < 0 ) continue; // muro, niente da fare

      G.setup_vertex( vij, vertex_label[i][j] );

      // cerco i vicini
      if ( j > 0 ) {
        int vL = vertex_pos[i][j-1];
        if ( vL >= 0 ) G.add_edge( vij, vL );
      }
      if ( j < ncol-1 ) {
        int vR = vertex_pos[i][j+1];
        if ( vR >= 0 ) G.add_edge( vij, vR );
      }
      if ( i > 0 ) {
        int vT = vertex_pos[i-1][j];
        if ( vT >= 0 ) G.add_edge( vij, vT );
      }
      if ( i < nrow-1 ) {
        int vB = vertex_pos[i+1][j];
        if ( vB >= 0 ) G.add_edge( vij, vB );
      }
    }
  }
}

int
main() {

  try {
    // leggo labirinto
    unsigned nrow, ncol, nvertex;
    vector<vector<int> >    vertex_pos;
    vector<vector<string> > vertex_label;

    read_maze( "maze1.txt", nrow, ncol, nvertex, vertex_pos, vertex_label );

    // costruzione grafo
    GraphLib::Graph G("maze");
    build_graph( nrow, ncol, nvertex, vertex_pos, vertex_label, G );

    G.dump(cout);
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
