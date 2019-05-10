/*\

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
#include <fstream>
#include <iomanip>   // maniopolazione dell I/O esemio setw, precision
#include <fstream>   // lettura/scrittura su file
#include <sstream>   // lettura/scrittura su stringa
#include <utility>   // STL pair
#include <set>       // STL set object
#include <algorithm> // STD std::transform
#include <string>    // STL string
#include <cmath>     // sin, cos funzioni matematiche di base
#include <string>    // C++ string
#include <exception> // std::exception
#include <cstdint>   // std::exception

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ostringstream;
using std::pair;
using std::set;
using std::vector;
using std::string;
using std::size_t;

static char const *fname[] = {
  "da-parole-italiane/1000_parole_italiane_comuni.txt",
  "da-parole-italiane/110000_parole_italiane_con_nomi_propri.txt",
  "da-parole-italiane/280000_parole_italiane.txt",
  "da-parole-italiane/400_parole_composte.txt",
  "da-parole-italiane/60000_parole_italiane.txt",
  "da-parole-italiane/660000_parole_italiane.txt",
  "da-parole-italiane/9000_nomi_propri.txt",
  "da-parole-italiane/95000_parole_italiane_con_nomi_propri.txt",
  "da-parole-italiane/parole_uniche.txt"
};

typedef set<string> Dictionary;

/*\

Funzione che legge dizionario da file

filename = nome del file
dic      = oggetto set che conterrà il dizionario

\*/

static
void
add_to_dictionary( string const & filename, Dictionary & dic ) {
  // file = oggetto per lettura da file
  ifstream file;
  // apro file in lettura, c_str() retituisce puntatore a char = stringa tipo C
  file.open( filename.c_str() );

  // controllo che il file sia aperto correttamente il lettura
  if ( ! file.good() ) {
    ostringstream ost;
    ost << "errore in apertura file: " << filename << "!";
    throw ost.str(); // lancio eccezzione con stringa C++ contenente descrizione errore
  }

  // leggo prima riga (numero) e la ignoro
  string line;
  getline( file, line, '\n');

  // loop lettura del file
  while ( file.good() ) {
    // legge una riga intera
    getline( file, line, '\n');

    //trasforma strinag in minuscolo
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);

    // piccolo parsing...
    if ( line[0] == '/' ) continue; // se commento passo alla riga successiva

    // line == parola da leggere, può contenere / verso la fine
    // cerca il primo carattere '/' nella stringa
    size_t pos = line.find('/');
    if ( pos != string::npos && pos > 1 ) {
      // trovato separatore, estre sottostringa
      dic.insert( line.substr( 0, pos ) );
    } else if ( line.length() > 1 ) {
      // non trovato separatore, uso stringa intera
      dic.insert( line );
    }
  }
}

int
main() {

  try {
    Dictionary italiano;
    for ( int i = 0; i < sizeof(fname)/sizeof(fname[0]); ++i )
      add_to_dictionary( fname[i], italiano );
    italiano.insert( "a" );
    italiano.insert( "é" );
    italiano.insert( "e" );
    italiano.insert( "i" );
    italiano.insert( "o" );
    // preposizioni accentate
    italiano.insert( "l'" );
    italiano.insert( "c'" );
    italiano.insert( "d'" );
    italiano.insert( "all'" );
    italiano.insert( "bell'" );
    italiano.insert( "quell'" );
    italiano.insert( "grand'" );
    italiano.insert( "pover'" );
    italiano.insert( "quest'" );
    italiano.insert( "dall'" );
    italiano.insert( "dell'" );
    italiano.insert( "nell'" );
    italiano.insert( "sull'" );
    cout << "TOTALE " << italiano.size() << " parole\n";
    ofstream file("italiano.dic");
    Dictionary::const_iterator it = italiano.begin();
    for ( ; it != italiano.end(); ++it ) file << *it << '\n';
    file.close();
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
