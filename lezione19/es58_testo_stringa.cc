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

static
void
testo_stringone( string const & filename, string & stringone ) {
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

  stringone = "";

  // leggo prima riga (numero) e la ignoro
  string line;

  // loop lettura del file
  while ( file.good() ) {
    // legge una riga intera
    getline( file, line, '\n');

    if ( line[0] == '#' ) continue; // salta commenti

    //trasforma strinag in minuscolo
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);

    // piccolo parsing...
    if ( line[0] == '/' ) continue; // se commento passo alla riga successiva

    for ( unsigned i=0;i < line.length(); ++i ) {
      char c = line[i];
      string cs = line.substr(i,1);
      if ( c >= 'a' && c <= 'z' ) { // accetto lettere minuscole
        stringone += c;
      } else if ( c >= 'A' && c <= 'Z' ) {
        stringone += char(tolower(c));
      } else if ( cs == "'" ||
                  cs == "à" ||
                  cs == "è" ||
                  cs == "ì" ||
                  cs == "ò" ||
                  cs == "ù" ||
                  cs == "á" ||
                  cs == "é" ||
                  cs == "í" ||
                  cs == "ó" ||
                  cs == "ú" ) {
        stringone += cs;
      }
    }
  }
}

int
main() {

  try {
    string stringone;
    testo_stringone( "testo-la-spada-nel-cuore.txt", stringone );
    ofstream file("stringone.txt");
    file << stringone << '\n';
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
