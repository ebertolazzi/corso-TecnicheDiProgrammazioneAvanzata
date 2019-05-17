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
  vector<vector<string> > & vertex_label,
  vector<string>          & rows
) {
  vertex_pos.clear();
  vertex_label.clear();
  rows.clear();

  // leggo labirinto e motto in vettore di stringhe
  ifstream file(fname);
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
          oss << i << " " << j;
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
  // croce
  int const ii1[] = {  1, 0, -1,  0 };
  int const jj1[] = {  0, 1,  0, -1 };
  // diagonale
  int const ii2[] = {  1, 1, -1, -1 };
  int const jj2[] = { -1, 1,  1, -1 };
  G.resize_vertex( nvertex );
  // costruisco grafo
  for ( int i = 0; i < nrow; ++i ) {
    for ( int j = 0; j < ncol; ++j ) {
      int vij = vertex_pos[i][j];
      if ( vij < 0 ) continue; // muro, niente da fare

      G.setup_vertex( vij, vertex_label[i][j] );

      // cerco i vicini croce
      for ( int k = 0; k < 4; ++k ) {
        int iii = i+ii1[k];
        int jjj = j+jj1[k];
        if ( iii < 0 || iii >= nrow || jjj < 0 || jjj >= ncol ) continue;
        int vv = vertex_pos[iii][jjj];
        if ( vv >= 0 ) G.add_edge( vij, vv );
      }
      // cerco i vicini diagonale
      /*
      for ( int k = 0; k < 4; ++k ) {
        int iii = i+ii2[k];
        int jjj = j+jj2[k];
        if ( iii < 0 || iii >= nrow || jjj < 0 || jjj >= ncol ) continue;
        int v1 = vertex_pos[iii][jjj];
        int v2 = vertex_pos[i][jjj];
        int v3 = vertex_pos[iii][j];
        if ( v1 >= 0 && (v2 >= 0 || v3 >= 0) ) G.add_edge( vij, v1 );
      }
      */
    }
  }
}

static
void
plot_maze( vector<string> const & rows ) {
  for ( unsigned i = 0; i < rows.size(); ++i )
    cout << rows[i] << '\n';
}

int
main() {

  try {
    // leggo labirinto
    unsigned nrow, ncol, nvertex;
    vector<vector<int> >    vertex_pos;
    vector<vector<string> > vertex_label;
    vector<string>          rows;

    read_maze( "maze1.txt", nrow, ncol, nvertex, vertex_pos, vertex_label, rows );
    plot_maze( rows );

    // costruzione grafo
    GraphLib::Graph G("maze");
    build_graph( nrow, ncol, nvertex, vertex_pos, vertex_label, G );

    unsigned in, out;
    for ( unsigned i = 0; i < G.numVertex(); ++i ) {
      if ( G.get_label(i) == "I" ) in  = i;
      if ( G.get_label(i) == "U" ) out = i;
    }

    cout << "in  = " << in  << '\n';
    cout << "out = " << out << '\n';

    GraphLib::Tree T("spanning tree");
    // cerca nodo in e out
    G.build_spanning_tree(T,in,false);

    // percorro spanning tree da foglia in uscita
    unsigned i = out;
    while ( ! T.is_root(i) ) {
      istringstream iss(T.get_label(i));
      unsigned ii, jj;
      iss >> ii >> jj;
      //cout << T.get_label(i) << '\n';
      rows[ii][jj] = '.';
      i = T.get_father( i );
    }

    cout << "\n\n";
    plot_maze( rows );

    //G.dump(cout);
    //T.dump(cout);
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
