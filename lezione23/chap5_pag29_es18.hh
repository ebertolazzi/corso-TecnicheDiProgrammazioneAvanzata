/*\
 |
 |   grafo A
 |
 |   O --- O --- O
 |   |     |
 |   O --- O --- O
 |      /  |     |
 |   O     O     O
 |
 |   numerazione
 |
 |   O --- 1 --- 2
 |   |     |
 |   3 --- 4 --- 5
 |      /  |     |
 |   6     7     8
\*/

#include <vector>
#include <string>

namespace gioco {

  using namespace std;

  typedef int integer;

  // vettore di edge del grafo A
  static integer E[][2] = {
    {0,1}, {1,0},
    {1,2}, {2,1},
    {0,3}, {3,0},
    {1,4}, {4,1},
    {3,4}, {4,3},
    {4,5}, {5,4},
    {4,6}, {6,4},
    {4,7}, {7,4},
    {5,8}, {8,5}
  };

  // conto edge del grafo usando sizeof
  static integer NE = sizeof(E)/sizeof(E[0]);

  class mini_grafo {
    vector<integer> vertex_connection[9];
  public:
    mini_grafo() {
      for ( integer i = 0; i < 9; ++i ) {
        vertex_connection[i].clear();
        vertex_connection[i].reserve(10);
      }
      for ( integer i = 0; i < NE; ++i ) {
        integer from = E[i][0];
        integer to   = E[i][1];
        //std::cout << "ADD: " << from << " --> " << to << '\n' ;
        vertex_connection[from].push_back(to);
      }
    }

    integer
    n_nearby( integer i ) const
    { return integer(vertex_connection[i].size()); }

    integer
    vertex( integer i, integer j ) const
    { return vertex_connection[i][j]; }

    void
    info( ostream & stream ) const {
      for ( integer i = 0; i < 9; ++i ) {
        for ( integer j = 0; j < n_nearby(i); ++j ) {
          stream << i << " --> " << vertex(i,j) << '\n';
        }
      }
    }
  };

  // controlla se ID corrisponde a configurazione valida
  static
  inline
  bool
  checkID( integer ID ) {
    integer AA = ID%10;
    integer BB = (ID/10) % 10;
    integer CC = ID/100;
    return AA < 9 && BB < 9 && CC < 9 && AA != BB && AA != CC && BB != CC;
  }

  class big_vertex {
    integer A, B, C;
  public:
    big_vertex() : A(0), B(1), C(2) {}

    void
    setup( integer _A, integer _B, integer _C ) {
      this->A = _A;
      this->B = _B;
      this->C = _C;
    }

    integer getA() const { return A; }
    integer getB() const { return B; }
    integer getC() const { return C; }

    // identificativo per distinguere le diverse configurazioni
    integer getID() const { return A+10*(B+10*C); }

    void
    setupByID( integer ID ) {
      this->setup( ID%10, (ID/10) % 10, ID/100 );
    }

    void
    plot( ostream & stream ) const {
      string lines[5];
      lines[0] = "O --- O --- O\n";
      lines[1] = "|     |      \n";
      lines[2] = "O --- O --- O\n";
      lines[3] = "   /  |     |\n";
      lines[4] = "O     O     O\n";
      lines[2*(A/3)][6*(A%3)] = 'A';
      lines[2*(B/3)][6*(B%3)] = 'B';
      lines[2*(C/3)][6*(C%3)] = 'C';
      for ( integer i = 0; i < 5; ++i ) stream << lines[i];
    }

    void
    build_nearby( vector<big_vertex> & list ) const {
      list.clear();
      list.reserve(10);
      mini_grafo mg;
      // costruisco la lista dei possibili vicini
      for ( integer iA = 0; iA < mg.n_nearby(A); ++iA ) {
        // mossa possibile di A, A = posizione attuale
        // newA = possibile posizione futura
        integer newA = mg.vertex( A, iA );
        for ( integer iB = 0; iB < mg.n_nearby(B); ++iB ) {
          // mossa possibile di B, B = posizione attuale
          // newB = possibile posizione futura
          integer newB = mg.vertex( B, iB );
          for ( integer iC = 0; iC < mg.n_nearby(C); ++iC ) {
            // mossa possibile di C, C = posizione attuale
            // newC = possibile posizione futura
            integer newC = mg.vertex( C, iC );

            /*\
              Ora si deve testare

              A --> newA
              B --> newB
              C --> newC

              che sia una mossa ammissibile, se si, si aggiunge alla lista
              dei vicini del grafo "grosso"

            \*/

            if ( newA == newB || newA == newC || newB == newC ) continue;

            // ok la mossa è accettata, inserisco nei primi vicini
            //cout << "Inserisce A = " << newA << " B = " << newB << " C = " << newC << '\n';
            big_vertex bv;
            bv.setup( newA, newB, newC );
            list.push_back( bv ); // implicito costruttore di copia
          }
        }
      }
    }
  };

  static integer ID_init    = 210; // ID nodo di partenza grafo delle configurazioni
  static integer ID_final[] = {
    678,
    786,
    867,
    687,
    768,
    876
  };

  class grafo_delle_configurazioni {
    // da vertice a vettore di interi con ID del nodo vicino
    vector<integer> vertex_connection[1000];
    vector<integer> father[1000]; // da usare per fare spanning tree
    integer nv;
    integer ne;
  public:

    // costruisce il grafo delle configurazioni
    grafo_delle_configurazioni() : nv(0), ne(0) {
      for ( integer ID = 0; ID < 1000; ++ID ) {
        vector<integer> & V = vertex_connection[ID];
        V.clear();
        V.reserve(10);
        if ( checkID( ID ) ) {
          ++nv;
          // è un vertice del grafo, costruisco i primi viconi
          vector<big_vertex> list;
          big_vertex BV;
          BV.setupByID( ID );
          BV.build_nearby( list );
          for ( vector<big_vertex>::const_iterator iV = list.begin();
                iV != list.end(); ++iV ) {
            V.push_back( iV->getID() );
            ++ne;
          }
        }
      }
      cout << "NV = " << nv << " NE = " << ne << '\n';
    }

    // dato un vertice tramite ID restituisce quanti vertici sono connessi
    integer
    n_nearby( integer ID ) const
    { return integer(vertex_connection[ID].size()); }

    // dato un vertice tramite ID restituisce ID del j-esimo vicino
    integer
    vertex( integer ID, integer j ) const
    { return vertex_connection[ID][j]; }

    // stampa grafo
    void
    info( ostream & stream ) const {
      for ( integer i = 0; i < 9; ++i ) {
        for ( integer j = 0; j < n_nearby(i); ++j ) {
          stream << i << " --> " << vertex(i,j) << '\n';
        }
      }
    }
  };
}
