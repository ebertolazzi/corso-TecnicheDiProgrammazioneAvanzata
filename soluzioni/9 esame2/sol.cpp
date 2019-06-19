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

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

static std::map<string,unsigned> md;

unsigned
min_delete( string const & str ) {

  std::map<string,unsigned>::const_iterator it = md.find( str );
  if ( it != md.end() ) return it->second;

  unsigned len = str.length();
  if ( len <= 1 ) return len;
  // cerca sottostringhe
  unsigned md_ott = len;

  // ottimizzo stringa sinistra
  unsigned ii = 0;
  while ( ++ii < len && str[ii-1] == str[ii] );
  // caso stringa unica
  if ( ii == len ) return 1;

  // ottimizzo stringa destra
  unsigned jj = len;
  while ( --jj > ii && str[jj-1] == str[jj] );

  for ( unsigned i = ii; i <= jj; ) {
    // ottimizzo C se caratteri tutti uguali espando C
    unsigned j = i;
    while ( ++j < jj && str[i] == str[j] );
    for (; j <= jj; ++j ) {
      string L = str.substr(0,i);
      string C = str.substr(i,j-i);
      string R = str.substr(j);
      unsigned mL = min_delete( L );
      unsigned mC = min_delete( C );
      unsigned mR = min_delete( R );
      unsigned md = mL + mC + mR;
      if ( L.length() > 0 && R.length() > 0 && L.back() == R.front() ) --md;
      if ( md < md_ott ) md_ott = md;
    }

    // ottimizzo L se caratteri tutti uguali
    unsigned next_i = i;
    while ( ++next_i <= jj && str[i] == str[next_i] );
    i = next_i;
  }
  md[str] = md_ott;
  return md_ott;
}
