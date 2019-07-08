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

 Soluzione efficiente:

 Programmazione dinamica su tabella (vettore).

\*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

unsigned
phi( unsigned nn ) {
  if ( nn < 3 ) return nn; // casi semplici
  std::vector<unsigned> table(nn+1);
  table[0] = 0;
  table[1] = 1;
  table[2] = 2;
  for ( unsigned n = 3; n <= nn; ++n ) {
    unsigned min_phi = n;
    unsigned pmax = n>>1;
    for ( unsigned p = 1; p <= pmax; ++p ) {
      unsigned q = n-p;
      unsigned r = table[p]+table[q];
      if ( r < min_phi ) min_phi = r;
    }
    pmax = unsigned(floor(sqrt(n)));
    for ( unsigned p = 2; p <= pmax; ++p ) {
      if ( (n % p) != 0 ) continue;
      unsigned q = n/p;
      unsigned r = table[p]+table[q];
      if ( r < min_phi ) min_phi = r;
    }
    table[n]  = min_phi;
  }
  return table[nn];
}

#if 0
int
main() {
  unsigned n = 31;
  unsigned m = phi(n);
  cout << "n = " << 31 << " m = " << m << '\n';
  return 0;
}
#endif
