/*\

\*/

#include "graph_lib.hh"
#include <fstream>

using namespace std;

int
main() {

  try {
    // leggo labirinto
    ifstream file("maze1.txt");
    vector<vector<int> > vertex_pos;
    vector<string> rows;
    while ( file.good() ) {
      string line;
      getline( file, line, '\n');
      if ( line.size() > 0 ) {
        rows.push_back(line);
        cout << "len = " << line.size() << '\n';
      }
      cout << line << '\n';
    }
    file.close();
    unsigned nrow = unsigned( rows.size() );
    unsigned ncol = unsigned( rows[0].size() );
    cout << "lette " << rows.size() << "righe\n";
    // costruzione grafo
    GraphLib::Graph G("maze");

    // conto i vertici del grafo associato al labirinto
    // e assegno numero consecutivo
    // inizializzo mappa (i,j)-> numero del vertice

    vertex_pos.resize(nrow);
    for ( unsigned i=0; i < nrow; ++i ) {
      vertex_pos[i].resize(ncol);
      std::fill(vertex_pos[i].begin(), vertex_pos[i].end(), -1 );
    }

    unsigned count = 0;
    for ( unsigned i = 0; i < nrow; ++i ) {
      for ( unsigned j = 0; j < ncol; ++j ) {
        char c = rows[i][j];
        if ( c == ' ' || c == 'I' || c == 'U' ) {
          // posizione libera, aggiungo vertice al grafo
          vertex_pos[i][j] = count++;
        }
      }
    }
    // so quanti sono i vertici, alloco memoria corrispondente
    G.resize_vertex( count );

    // costruisco grafo
    for ( unsigned i = 0; i < nrow; ++i ) {
      for ( unsigned j = 0; j < ncol; ++j ) {
        int vij = vertex_pos[i][j];

        if ( vij < 0 ) continue; // muro, niente da fare

        char c  = rows[i][j];
        if ( c == 'I' ) G.setup_vertex( vij, "Ingresso" );
        if ( c == 'U' ) G.setup_vertex( vij, "Uscita" );

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
