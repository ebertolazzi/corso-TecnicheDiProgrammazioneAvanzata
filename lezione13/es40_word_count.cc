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
  file.close() ;
  
  // write the output
  for ( map<string,int>::const_iterator i = wc.begin() ; i != wc.end() ; ++i ) {
    string parola = string("'") + i -> first + string("'");
    cout << "parola = " << setw(15) << left << parola << " frequenza = " << i -> second << "\n" ;
  }
}
