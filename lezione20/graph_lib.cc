/*\

\*/

#include "graph_lib.hh"
#include <deque>

namespace GraphLib {

  using namespace std;

  void
  Graph::build_spanning_tree( Tree & T, unsigned v0, bool BFS ) {
    T.resize_vertex( this->numVertex() );
    // inizializza i vertici dello spanning tree
    for ( unsigned i = 0; i < this->numVertex(); ++i )
      T.setup_vertex( i, this->V[i].get_label() );

    // mark all vertex as not visited
    vector<bool> visited(this->numVertex());
    fill( visited.begin(), visited.end(), false );

    deque<unsigned> front;
    front.push_back(v0);
    visited[v0] = true; // v0 è root, marca come visitata

    while ( front.size() > 0 ) {
      unsigned father;
      if ( BFS ) { father = front.front(); front.pop_front(); }
      else       { father = front.back();  front.pop_back();  }
      visited[father] = true;
      Vertex const & vrt = this->V[father]; // prendo nodo e cerco figli
      for ( unsigned j = 0; j < vrt.degree(); ++j ) {
        unsigned son = vrt.get_neighbor( j );
        if ( visited[son] ) continue; // gia visitato, skip
        // trovato nuovo nodo, marco come visitato, aggiungo al fronte
        // e inserisco nello spanning tree
        visited[son] = true;
        T.setup( son, father );
        front.push_back( son );
      }
    }
  }

}
