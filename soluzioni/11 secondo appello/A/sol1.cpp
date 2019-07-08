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

/*\

Soluzione con memoizzazione che usa map.
Semplice ma poco efficiente.

\*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

static std::map<unsigned,unsigned> md;

unsigned
phi( unsigned n ) {
  if ( n == 1 ) return 1;

  std::map<unsigned,unsigned>::const_iterator it = md.find( n );
  if ( it != md.end() ) return it->second;

  unsigned min_phi = n;
  unsigned pmax = n>>1;
  for ( unsigned p = 1; p <= pmax; ++p ) {
    unsigned q = n-p;
    unsigned r = phi(p)+phi(q);
    if ( r < min_phi ) min_phi = r;
  }
  pmax = unsigned(floor(sqrt(n)));
  for ( unsigned p = 2; p <= pmax; ++p ) {
    if ( (n % p) != 0 ) continue;
    unsigned q = n/p;
    unsigned r = phi(p)+phi(q);
    if ( r < min_phi ) min_phi = r;
  }

  md[n] = min_phi;
  return min_phi;
}
