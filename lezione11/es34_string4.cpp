/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
:|:
\*/

#include "course_lib.h"
#include <iostream>
#include <algorithm> // per std::swap
#include <string> // stringhe C++

using namespace std;

int
main() {
  string s1("pippo");
  string s2("pluto");
  string s3 = s1; // String s3(s1);

  s3 = s1; // chiama operatore di copia
  cout << "s3 = " << s3 << '\n';
  s3 += " paperino";
  cout << "s3 = " << s3 << '\n';
  cout << "s3.length() = " << s3.length() << '\n';
  cout << "s3.capacity() = " << s3.capacity() << '\n';
  s3 += " ddddddddddddddddddddd";
  cout << "s3 = " << s3 << '\n';
  cout << "s3.length() = " << s3.length() << '\n';
  cout << "s3.capacity() = " << s3.capacity() << '\n';
  s3 += "eee";
  cout << "s3 = " << s3 << '\n';
  cout << "s3.length() = " << s3.length() << '\n';
  cout << "s3.capacity() = " << s3.capacity() << '\n';
  cout << "s3[3] = " << s3[3] << '\n';
  cout << "s3.back() = " << s3.back() << '\n';
  cout << "s3.front() = " << s3.front() << '\n';

  s3.clear();
  cout << "s3 = " << s3 << '\n';
  cout << "s3.length() = " << s3.length() << '\n';
  cout << "s3.capacity() = " << s3.capacity() << '\n';

  s3.c_str() ; // ritorna char const * puntatore alla stringa C
  return 0;
};
