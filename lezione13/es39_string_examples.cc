/*
  A simple program to test string class
 */

#include <iostream> // for I/O
#include <iomanip>  // for hex, dec, width
#include <string>   // string support

// carico namespace std per evitare di scrivere std:: ogni volta
// che uso una funzione di std.
using namespace std;

int
main() {
  // costruisco 4 stringhe, 2 sono inizilizzate alla stringa ""
  // due sono inizializzate esplicitamente
  string a, b, c("$$$"), d = "pippo";
  //                          ^
  //                          |
  // -------------------------
  // inizilizzazione equivalente a d("pippo")
  // e richiama il costruttore string( char const [] )
  
  a = d; // fa copia della stringa d nella stringa a

  void const * pobja = &a; // get the pointer to the C-string of a
  void const * pobjd = &d; // get the pointer to the C-string of d

  char const * pa = a.c_str(); // get the pointer to the C-string of a
  char const * pd = d.c_str(); // get the pointer to the C-string of d

  cout << "pa - pd " << pa-pd << '\n';

  cout << hex; // da adesso in poi tutti goli interi sono stampati in esadecimale
  cout << "address of the object string a = " << setw(10) << reinterpret_cast<unsigned long>(pobja) << '\n' ;
  cout << "address of the object string d = " << setw(10) << reinterpret_cast<unsigned long>(pobjd) << '\n' ;

  cout << "address of string contained in object a = " << setw(10) << reinterpret_cast<unsigned long>(pa) << '\n' ;
  cout << "address of string contained in object d = " << setw(10) << reinterpret_cast<unsigned long>(pd) << '\n' ;
  //
  //                                   ^       ^               ^
  // use hexadecimal numer  -----------+       |               |
  // set width for next output to 10 charater -+               |
  // cast: convert type from pointer to unsigned integer ------+

  a += " pluto"; // concateno in coda alla stringa a (oggetto STL) la stringa "pluto" (C-sgring)
  cout << "a = '" << a << "'\n" ;
  cout << "b = '" << b << "'\n" ;

  pa = a.c_str() ; // get the pointer to the C-string of a
  pd = d.c_str() ; // get the pointer to the C-string of d

  cout << "address of string contained in object a = " << setw(10) << reinterpret_cast<unsigned long>(pa) << '\n' ;
  cout << "address of string contained in object d = " << setw(10) << reinterpret_cast<unsigned long>(pd) << '\n' ;
  cout << dec << '\n'; // rispristino stampa degli interi in formato decimale

  // main operation on string
  // concatenation, concatenate string a and c
  b = a+c ;
  cout << "a   = '" << a << "'\n" ;
  cout << "c   = '" << c << "'\n" ;
  cout << "a+c = '" << b << "'\n" ;
  
  // find
  int i = a.find("plut") ;
  cout << "a.find(\"plut\") = " << i << "\n";

  i = a.find("asx") ;
  cout << "a.find(\"asx\") = " << i << "\n";
  
  // comparison
  a = "pippo" ;
  b = "pluto" ; 
  c = "paperino" ;
  d = "pippo" ;
  cout << "a = '" << a << "'\n" ;
  cout << "b = '" << b << "'\n" ;
  cout << "c = '" << c << "'\n" ;
  cout << "d = '" << d << "'\n" ;
  
  cout << "'" << a << "' < '" << b << "' = " ;
  if ( a < b ) cout << "true\n" ;
  else         cout << "false\n" ;

  cout << "'" << a <<"' > '" << c << "' = " ;
  if ( a > c ) cout << "true\n" ;
  else         cout << "false\n" ;

  cout << "'" << a <<"' == '" << d << "' = " ;
  if ( a == d ) cout << "true\n" ;
  else          cout << "false\n" ;

  cout << "'" << b <<"' >= '" << c << "' = " ;
  if ( b >= c ) cout << "true\n" ;
  else          cout << "false\n" ;

  cout << "'" << c <<"' >= '" << a << "' = " ;
  if ( c >= a ) cout << "true\n" ;
  else          cout << "false\n" ;

  cout << "'a' >= '@' = " ;
  // confronta i puntatore che punta a "a"
  // con il puntatore  che punta a "@"
  if ( "a" >= "@" ) cout << "true\n" ;
  else              cout << "false\n" ;

  cout << "'a' >= '@' = " ;
  // confronta i puntatore che punta a "a"
  // con il puntatore  che punta a "@"
  if ( string("a") >= "@" ) cout << "true\n" ;
  else                      cout << "false\n" ;

  cout << "'a' >= '@' = " ;
  // confronta i puntatore che punta a "a"
  // con il puntatore  che punta a "@"
  // 1 = "a" > "@"
  // 0 = "a" == "@"
  // -1 = "a" < "@"
  cout << "strcmp(\"a\",\"@\") = " << strcmp("a","@") << '\n' ;

  cout << "'#' >= '%' = " ;
  if ( string("#") >= "%" ) cout << "true\n" ;
  else                      cout << "false\n" ;

  cout << "strcmp(\"#\",\"%\") = " << strcmp("#","%") << '\n' ;

}

