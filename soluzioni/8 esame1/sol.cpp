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
stringona( unsigned nmax, unsigned ndivide, string & res ) {
  res = "";
  for ( unsigned i = 1; i <= nmax; ++i ) {
    if ( (i % ndivide) == 0 ) {
      char str[100];
      sprintf( str, "%d", i );
      res += str;
    }
  }
}
