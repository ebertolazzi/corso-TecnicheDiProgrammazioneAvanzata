/*
  A simple program that count words from a file
  and print with some statistics.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

// from STL
#include <string>
#include <map>
#include <vector>

/*
  > main pippo pluto

  argc = 3
  argv[0] = "main"
  argv[1] = "pippo"
  argv[2] = "pluto"
  
  Usage of the program
  
  > main filename
  
 */
 
using namespace std ;

// comparator for sort (ascending order)
struct less_than {
  //! return always true
  bool operator () (pair<string,int> const & pa, pair<string,int> const & pb) const {
    if ( pa.second < pb.second ) return true ;
    if ( pa.second == pb.second ) {
      return pa.first < pb.first;
    }
    return false;
  }
};

// comparator for sort (sescending order)
struct greater_than {
  //! return always true
  bool operator () (pair<string,int> const & pa, pair<string,int> const & pb) const {
    if ( pa.second > pb.second ) return true ;
    if ( pa.second == pb.second ) {
      return pa.first > pb.first;
    }
    return false;
  }
};

static struct less_than    lt ;
static struct greater_than gt ;

int
main( int argc, char * argv[] ) {
  string fileName ;

  if ( argc > 2 ) {
    // too nuch argument, issue an error
    cerr << "usage: " << argv[0] << " file\n" ;
    return 1 ;
  }

  if ( argc == 1 ) {
    // only one argument, ask to the user the file name
    cout << "File: " ;
    cin >> fileName ; 
  } else {
    // two argument, get file name from command line
    fileName = argv[1] ;
  }
  
  // open the file
  // ifstream = tipo oggetto file in lettura
  // si aspetta stringa tipo "C" come filename quindi devo usare c_str()
  ifstream file( fileName.c_str() ) ;

  // equivalentemente
  // ifstream file;
  // file.open( fileName.c_str() );
  
  // check if the file exist is opened etc.
  if ( file.bad() ) {
    cerr << "error in openeing : " << fileName << "\n" ;    
    return 1 ; 
  }

  // "stringa" (string) = quante volte compare (int)
  map<string,int> wc ; // associative array to store word count
  
  // loop to read all the words
  while ( file.good() ) { // true se file aperto senza errori e non a fine file
    string w;
    file >> w; // leggo stringa e copio in oggetto stringa w
               // di default gli spazi vengono ignorati e usati come separatori
               // delle parole

    // filtro per togliere elementi spuri
    // --> minuscole
    /* modo barbaro
    string ww;
    for ( string::const_iterator is = w.begin(); is != w.end(); ++is )
      ww += char(toupper( int(*is) ));
    */
    // modo elegante
    // ::tolower cerco la funzione non in std ma comne fiunzione C
    std::transform(w.begin(), w.end(), w.begin(),::tolower);

    // eliminazione dei caratteri non "a-z" in testa e in coda
    while ( w.length() > 0 && !isalpha(w.back()) ) w.pop_back();
    while ( w.length() > 0 && !isalpha(w.front()) ) w.erase(0); // cancella carattere iniziale

    if (  w.length() == 0 ) continue; // salta catalogazione se parola vuota

    // cerco all'interno della mappa (array associativo) un elemento con chiave
    // la stringa w
    map<string,int>::iterator i = wc.find(w) ;
    if ( i == wc.end() ) {
      // element not found
      wc[w] = 1; // creo elemento con chiave w e inizializzo a 1 il suo valore
    } else {
      // elemento trovato posso incrementarlo con wc[w]++;
      // ma wc[w] implica la ricerca dell'elemento nella mappa
      // elemento che ho gia trovato con iteratore `i`
      // i->first  keyword (string)
      // i->second value   (int)
      i->second++;
    }
  }

  // close the file
  file.close();

  // salvo parole oridinate in vettore e ordino in base alla frequenza
  // define a vector to store the results
  vector< pair<string,int> > vec ;
  copy( wc.begin(), wc.end(), back_inserter(vec) ) ;

  // the code is equivalent to
  // for ( map<string,int>::const_iterator i = wc.begin() ;
  //       i != wc . end() ; ++i )
  //   vec . push_back(*i) ;
  //
  // the "back_inserter" function return an object which implement
  // the operator ++ and =. ++ do nothing while
  // back_inserter(vec) = rhs
  // is transformed to vec.push_back(rhs)!.

  // sort the vector
  sort( vec.begin(), vec.end(), gt );

  // write the output
  int nmax = 10;
  for ( vector<pair<string,int> >::const_iterator i = vec.begin() ;
        i != vec.end() && nmax-- > 0 ; ++i ) {
    cout << "word = " << setw(10) << left << i -> first
         << " counted N. " << i -> second << " times\n" ;
  }
}
