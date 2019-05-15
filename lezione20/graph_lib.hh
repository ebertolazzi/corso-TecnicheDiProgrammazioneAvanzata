/*\

\*/

#include <iostream>  // I/O del C++
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <sstream>   // lettura/scrittura su stringa
#include <utility>   // STL pair
#include <vector>    // STL vector object
#include <algorithm> // STD std::transform
#include <string>    // STL string
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <cstdint>   // std::exception

namespace GraphLib {

  using namespace std;

  class Vertex;
  class Vertex_of_a_tree;
  class Edge;
  class Graph;
  class Tree;

  /*\

    class vertice, memorizza i primi vicini di un vertice in un grafo.
    Viene memorizzata la posizione (numero unsigned)
    nella lista (vettore STL) dei vertici.

  \*/
  class Vertex {
    string           label;
    vector<unsigned> neighbors_pos;
  public:

    Vertex() : label("") {}

    // inizializza il nodo con 0 vicini e un nome
    void
    setup( string const & name ) {
      this->label = name;
      this->neighbors_pos.clear();
    }

    // restituisce il grado del nodo = numero di vicini
    unsigned
    degree() const
    { return unsigned( this->neighbors_pos.size() ) ; }

    // aggiunge un vicino al nodo (posizione del vicino)
    void
    add_neighbor( unsigned pos ) {
      this->neighbors_pos.push_back( pos );
    }

    // aggiunge un vicino al nodo (posizione del vicino)
    void
    delete_neighbor( unsigned pos ) {
      vector<unsigned>::iterator ipos = find(this->neighbors_pos.begin(),
                                             this->neighbors_pos.end(),
                                             pos );
      if ( ipos != this->neighbors_pos.end() ) this->neighbors_pos.erase( ipos );
    }

    // restituisce posizione del vicini i-esimo
    unsigned
    get_neighbor( unsigned ipos ) const
    { return this->neighbors_pos[ipos]; }

    // stampa vertice con posizione dei suoi vicini
    void
    dump( ostream & stream ) const {
      stream
        << this->label << " ->";
      vector<unsigned>::const_iterator iv = this->neighbors_pos.begin();
      for ( ; iv != this->neighbors_pos.end(); ++iv )
        stream << ' ' << setw(3) << *iv;
      stream << '\n';
    }

  };

  /*\
    Vertice di un Albero, non serve memorizzare i figli
    per gli algoritmi che intendiamo implementare
  \*/
  class Vertex_of_a_tree {
    string   label;
    unsigned father_pos;
  public:

    // inizializza il vertice con un nome e la posizione del padre
    // in caso di root father = ~unsigned(0) ( tutti i bit a 1 )
    void
    setup( unsigned father ) {
      this->father_pos = father;
    }

    // inizializza il vertice con un nome e la posizione del padre
    // in caso di root father = ~unsigned(0) ( tutti i bit a 1 )
    void
    setup( string const & name, unsigned father ) {
      this->label      = name;
      this->father_pos = father;
    }

    // inizializza il vertice con come "root" (radice) dell'albero
    void
    setup( string const & name ) {
      this->label      = name;
      this->father_pos = ~unsigned(0);
    }

    // restituisce la posizione del vertice "padre" nel grafo
    unsigned
    get_father() const
    { return this->father_pos; }

    // true se il vertice è la root dell'albero
    bool
    is_root() const
    { return this->father_pos == ~unsigned(0); }

  };

  class Edge {
    string   label;
    unsigned from_pos;
    unsigned to_pos;
  public:

  };

  /*\
   Classe che memorizza un grafo generico nel vettore di vertici V.
   Ogni vertice ha la lista dei suoi vicini cosicche il grafo
   non necessita di altri dati.
  \*/
  class Graph {
    string         label;
    vector<Vertex> V;
  public:

    // inizializza il grafo ad un grafo vuoto
    Graph( string const & name ) : label(name) {}

    // restituisce il numero totale dei vertici
    unsigned
    numVertex() const {
      return unsigned( V.size() );
    }

    /*\
      Inizializza la lista dei vertici (vettore STL)
      ad nv vertici isolati
    \*/
    void
    resize_vertex( unsigned nv ) {
      V.clear();
      V.resize( size_t(nv) );
    }

    // da un nome al vertice i-esimo ed eventualmente cancella i suoi vicini
    void
    setup_vertex( unsigned i, string const & name ) {
      this->V[i].setup( name );
    }

    // aggiungo edge al grafo modificando i vicini
    // dei vertici corrispondenti
    void
    add_edge( unsigned from, unsigned to ) {
      this->V[from].add_neighbor( to );
    }

    void
    add_edge_undirected( unsigned from, unsigned to ) {
      this->V[from].add_neighbor( to );
      this->V[to].add_neighbor( from );
    }

    // aggiungo edge al grafo modificando i vicini
    // dei vertici corrispondenti
    void
    delete_edge( unsigned from, unsigned to ) {
      this->V[from].delete_neighbor( to );
    }

    void
    delete_edge_undirected( unsigned from, unsigned to ) {
      this->V[from].delete_neighbor( to );
      this->V[to].delete_neighbor( from );
    }

    void
    build_spanning_tree( Tree & T, unsigned v0 );

    void
    dump( ostream & stream ) const {
      vector<Vertex>::const_iterator iV = V.begin();
      for ( ; iV != V.end(); ++iV ) {
        stream << "V n." << (iV-V.begin()) << ':' ;
        iV->dump( stream );
      }
    }
  };

  class Tree {
    string                   label;
    vector<Vertex_of_a_tree> V;
  public:

    // inizializza il grafo ad un grafo vuoto
    Tree( string const & name ) : label(name) {}

    // restituisce il numero totale dei vertici
    unsigned
    numVertex() const {
      return unsigned( V.size() );
    }

    /*\
      Inizializza la lista dei vertici (vettore STL)
      ad nv vertici isolati
    \*/
    void
    resize_vertex( unsigned nv ) {
      V.clear();
      V.resize( size_t(nv) );
    }

    // da un nome al vertice i-esimo ed eventualmente cancella i suoi vicini
    void
    setup_vertex( unsigned i, string const & name ) {
      this->V[i].setup( name );
    }

    // aggiungo edge al grafo modificando i vicini
    // dei vertici corrispondenti
    void
    setup( unsigned sun, unsigned father ) {
      this->V[sun].setup( father );
    }

  };


}
