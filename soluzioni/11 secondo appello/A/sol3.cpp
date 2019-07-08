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

/*
 soluzione con anche la costruzione della espressione
 che minimizza `1`
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <string>

using namespace std;

pair<unsigned,string>
phi( unsigned nn ) {
  std::vector<unsigned> table(nn+1);
  std::vector<string>   stable(nn+1);
  table[0] = 0; stable[0] = "";
  table[1] = 1; stable[1] = "1";
  table[2] = 2; stable[2] = "1+1";
  table[3] = 3; stable[3] = "1+1+1";
  table[4] = 4; stable[4] = "1+1+1+1";
  table[5] = 5; stable[5] = "1+1+1+1+1";
  for ( unsigned n = 6; n <= nn; ++n ) {
    unsigned min_phi = n;
    string   smin    = "";
    unsigned pmax = n>>1;
    for ( unsigned p = 1; p <= pmax; ++p ) {
      unsigned q = n-p;
      unsigned r = table[p]+table[q];
      string rr = "(";
      rr += stable[p]; rr += ") + ("; rr += stable[q]; rr += ")";
      if ( r < min_phi ) { min_phi = r; smin = rr; }
    }
    pmax = unsigned(floor(sqrt(n)));
    for ( unsigned p = 2; p <= pmax; ++p ) {
      if ( (n % p) != 0 ) continue;
      unsigned q = n/p;
      unsigned r = table[p]+table[q];
      string rr = "(";
      rr += stable[p]; rr += ") * ("; rr += stable[q]; rr += ")";
      if ( r < min_phi ) { min_phi = r; smin = rr; }
    }
    table[n]  = min_phi;
    stable[n] = smin;
  }
  return pair<unsigned,string>(table[nn],stable[nn]);
}

#if 1

int
main() {
  unsigned n = 31;
  pair<unsigned,string> res = phi(n);

  cout << "phi(" << 31 << ") = " << res.first << '\n';
  cout << res.second << '\n';

  return 0;

}

#endif
