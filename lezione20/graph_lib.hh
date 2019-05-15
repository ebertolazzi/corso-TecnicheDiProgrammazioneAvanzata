/*\

\*/

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <sstream>   // lettura/scrittura su stringa
#include <utility>   // STL pair
#include <set>       // STL set object
#include <algorithm> // STD std::transform
#include <string>    // STL string
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <cstdint>   // std::exception

namespace GraphLib {

  class Vertex;
  class Vertex_of_a_tree;
  class Edge;
  class Graph;
  class Tree;

  class Vertex {
    string           label;
    vector<unsigned> neighbors_pos;
  public:

    Vertex() {}

    void
    setup( string const & name ) {
      this->label = name;
      this->neighbors_pos.clear();
    }

    unsigned
    degree() const
    { return unsigned( this->neighbors_pos.size() ) ; }

    void
    add_neighbor( unsigned pos ) {
      this->neighbors_pos.push_back( pos );
    }

    unsigned
    get_neighbor( unsigned ipos ) const
    { return this->neighbors_pos[ipos]; }

  };

  class Vertex_of_a_tree {
    string   label;
    unsigned father_pos;
  public:

    void
    setup( string const & name, unsigned father ) {
      this->label      = name;
      this->father_pos = father;
    }

    unsigned
    get_father() const
    { return this->father_pos; }

  };

  class Edge {
    string   label;
    unsigned from_pos;
    unsigned to_pos;
  public:

  };

  class Graph {
    vector<Vertex> V;
  public:

    void
    add_edge( unsigned from, unsigned to ) {
      this->V[from].add_neighbor( to );
    }

    void
    add_edge_undirected( unsigned from, unsigned to ) {
      this->V[from].add_neighbor( to );
      this->V[to].add_neighbor( from );
    }

    void
    build_spanning_tree( Tree & T, unsigned v0 );

  };

  class Tree {
    vector<Vertex_of_a_tree> V;
  public:

  };


}
