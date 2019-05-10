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

typedef set<string> Dictionary;

static
void
read_dictionary( string const & filename, Dictionary & dic ) {
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
  // loop lettura del file
  while ( file.good() ) {
    // legge una riga intera
    string line;
    getline( file, line, '\n');
    dic.insert( line );
  }
}

static
bool
is_a_word( string const & w, Dictionary const & dic ) {
  Dictionary::const_iterator it = dic.find( w );
  return !( it == dic.end() );
}

static
bool
is_splittable( string const & w, Dictionary const & dic ) {
  // da riempire
  return true;
}

static
bool
is_splittable2(
  string     const & w,
  Dictionary const & dic,
  vector<string>   & parole ) {
  // da riempire
  return true;
}

int
main() {

  try {
    Dictionary italiano;
    string stringone;
    ifstream file("stringone.txt");
    file >> stringone;
    file.close();
    cout << "letto:" << stringone << '\n';
    read_dictionary( "italiano.dic", italiano );
    bool ok = is_splittable( stringone, italiano );
    cout << "spezzabile ?" << (ok?"SI":"NO") << '\n';
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
