/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi e prof. Andrea Del Prete
:|:
:|:
\*/

#include <fstream>
#include <vector>

using namespace std;

void
string_vec( unsigned n, unsigned const vec[], string & res ) {
  res = "";
  for ( unsigned i = 0; i < n; ++i ) {
    char str[100];
    sprintf( str, "%d", vec[i]+i );
    res += str;
  }
}
