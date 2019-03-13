/*
  Sono un commento multilinea

*/

// commento singola linea (C++)
// include ~ require (ruby)
// iostream = Input Output Stream
#include <iostream>
// <....> <= cerca il file nelle
// directory di sistema
// 

/*
  namespace ~ Module (Ruby)
*/
// usiamo le "funzioni" del comntenitore
// std definito nel file "iostream"
using namespace std;

// int = intero
int
main() // entry point del programma
// { corpo della funzione }
{
   // cout = character out
   // endl = andare a capo
   // "\n" carattere andare a capo
   cout << "Hello World\n" ;
   // cout = oggetto C++, in C si usa printf
   return 0; // esce dal programma e restiuisce 0
}

/*
  Per compilare il programma

  CXX es1.cpp -o es1

  CXX = g++     su linux o windows con mingw
  CXX = clang++ su mac
*/
