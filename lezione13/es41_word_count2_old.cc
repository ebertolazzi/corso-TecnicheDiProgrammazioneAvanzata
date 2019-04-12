/*
  A simple program that count word from a file
  and print with some statistics.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cctype>

// from STL
#include <string>
#include <vector>
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


// comparator for sort (ascending order)
typedef struct less_than {
  //! return always true
  bool operator () (pair<string,int> pa, pair<string,int> pb) const {
    if ( pa . second < pb . second ) return true ;
    if ( pa . second == pb . second ) {
      return pa . first < pb . first ;
    }
    return false ;
  }
} ;

// comparator for sort (sescending order)
typedef struct greater_than {
  //! return always true
  bool operator () (pair<string,int> pa, pair<string,int> pb) const {
    if ( pa . second > pb . second ) return true ;
    if ( pa . second == pb . second ) {
      return pa . first > pb . first ;
    }
    return false ;
  }
} ;

less_than    lt ;
greater_than gt ;

int
main( int argc, char * argv[] ) {
  string fileName ;

  if ( argc > 2 ) {
    // too much argument, issue an error
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
  ifstream file( fileName . c_str() ) ;
  
  // check if the file exist is opened etc.
  if ( file . bad() ) {
    cerr << "error in openeing : " << fileName << "\n" ;    
    return 1 ; 
  }
  
  map<string,int> wc ; // word count
  
  // loop to read all the words
  while ( file . good() ) {
    string w1, w ;
    file >> w1 ;
    w = "" ;
    for ( string::iterator i = w1.begin() ; i != w1.end() ; ++i ) {
      // string::value_type is the type of the element of the string
      // normally string::value_type == char
      string::value_type c = tolower(*i) ;
      // consider only letters
      if ( isalpha(c) ) w . push_back(c) ;
    }
    
    // check if w is present in the associative array wc
    map<string,int>::iterator i = wc.find(w) ;
    if ( i == wc.end() ) {
      // element not found, create and initailize to 1
      // only if lenght > 0 
      if ( w . length() > 0 ) wc[w] = 1 ;
    } else {
      // element found!
      i->second++ ;
    }
    
  }

  // close the file
  file . close() ;
  
  // define a vector to store the results
  vector<pair<string,int> > vec ;
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
  int nmax = 10 ;
  for ( vector<pair<string,int> >::const_iterator i = vec.begin() ;
        i != vec.end() && nmax-- > 0 ; ++i ) {
    cout << "word = " << setw(10) << left << i -> first
         << " counted N. " << i -> second << " times\n" ;
  }
}