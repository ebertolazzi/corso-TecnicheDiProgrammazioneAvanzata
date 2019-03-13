/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi e prof. Andrea Del Prete
:|:
:|:
\*/

#include "course_lib.h"
#include <fstream>

using namespace std;

/*\
:|: Ordinamento heapsort, vedi note online
:|: per la descrizione
\*/

// C++ program for implementation of Heap Sort
#include <iostream>

using namespace std;

void
dot_heap( std::ostream & file, int arr[], int N ) {
  file
    << "digraph G {\n"
    << "  nodesep=0.8;\n"
    << "  ranksep=0.5;\n" ;
  int son = N;
  while ( --son > 0 ) {
    int father = (son-1)>>1;
    file << "  " << father << " -> " << son << ";\n";
  }
  file
    << "}\n"
    << "# dot -Tpng file.dot > file.png\n";
}
int
main() {
  int N = 50;
  int v[N];
  Random rgen;
  TicToc tm;
  for ( int i = 0; i < N; ++i )
    v[i] = int(rgen.dice( -100, 100 ));

  /*\
    ofstream = dichiara oggetto per scrittura su file
    ifstream = dichiara oggetto per lettura da file

    ofstream file("nome del file"); // definisce file oggetto per scrittura su file

    oppure

    ofstream file;
    file.open("nome del file");

    ifstream file("nome del file"); // definisce file oggetto per leggere da file

    oppure

    ifstream file;
    file.open("nome del file");

    quando si è finito di scrivere o leggere

    file.close();

    file si usa come "cout" per la scrittura
    file si usa come "cin" per la lettura

  \*/
  ofstream file("out.dot");
  dot_heap( file, v, N );
  file.close();
  return 0;
};
