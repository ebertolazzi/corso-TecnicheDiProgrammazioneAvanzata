/*\

\*/

#include "course_lib.h" // per usare generator numeri casuali

#include <iostream>  // I/O del C++
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
using std::ostringstream;
using std::pair;
using std::set;
using std::vector;
using std::string;
using std::size_t;

typedef set<string> Dictionary;

/*\

Funzione che legge dizionario da file

filename = nome del file
dic      = oggetto set che conterrà il dizionario
\*/
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
  dic.insert( "a" );
  dic.insert( "i" );
  dic.insert( "e" );
  dic.insert( "o" );
  dic.insert( "é" );
  cout << "lette " << dic.size() << " parole dal file: " << filename << '\n';
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
  bool ok = false;
  //cout << "ENTRA\n";
  for ( unsigned k=1; k <= w.length() && !ok; ++k ) {
    string wl = w.substr( 0, k );
    //cout << "wl = " << wl << '\n';
    if ( is_a_word( wl, dic ) ) {
      string wr = w.substr( k );
      //cout << "wl,wr = " << wl << "," << wr << '\n';
      if ( wr.length() > 0 ) {
        ok = is_splittable( wr, dic );
        //cout << "ok = " << ok << "\n";
      } else {
        ok = true;
      }
    }
  }
  //cout << "ESCE\n";
  return ok;
}

static
void
InterpunctioVerborum( string const & w, vector<string> & words ) {
}

string stringona = "minibikedaiaiannieventiatrentoilminicrossorganizzatodallassociazionesportivagsapovoèormaiallatredicesimaedizioneeprometteanchequestannodivertimentoedallegriapergrandiepicciniilmiticoziobertoconlasuaofficinavolantegarantiràinterventimeccanicieinsegneràaibambiniaprendersicuradelpropriomezzocascoobbligatorionutellapartypertuttiallafineepremiadestrazioneconcluderannoilpomeriggiovenitenumerosi";

int
main() {

  try {
    Dictionary italian;
    read_dictionary( "Italian.dic", italian );

    cout
      << "pippo è nel dizionario? "
      << ( is_a_word( "pippo", italian ) ?  "VERO" : "FALSO" )
      << '\n';

    cout
      << "amaca è nel dizionario? "
      << ( is_a_word( "amaca", italian ) ?  "VERO" : "FALSO" )
      << '\n';

    // aggiungo parole al dizionario
    italian.insert("minibike");
    italian.insert("eventi");
    italian.insert("trento");
    italian.insert("miniCross");
    italian.insert("gsa");
    italian.insert("povo");
    italian.insert("tredicesima");
    italian.insert("piccini");
    italian.insert("berto");
    italian.insert("nutella");
    italian.insert("party");

    //stringona = "minibikeeventik";
    stringona = "minibikeeventitredicesimabertopiccini";

    cout
      << ( is_splittable( stringona, italian ) ?  "VERO" : "FALSO" )
      << '\n';

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
