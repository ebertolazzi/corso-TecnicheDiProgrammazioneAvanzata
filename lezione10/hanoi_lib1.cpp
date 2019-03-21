/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
:|:
:|:
\*/

#include "hanoi_lib1.h"

#include <iostream>
#include <iomanip> // per setw
#include <algorithm> // per std::swap
#include <string> // per std::swap
#include <vector>

using namespace std;

bool
hanoi_init( Hanoi_status & h, int N ) {
  if ( N > N_MAX_DISK || N <= 0 ) {
    cerr
      << "hanoi_init, N = " << N
      << " deve essere <= " << N_MAX_DISK
      << " e maggiore di 0\n";
    return false;
  }
  h.N    = h.n[0] = N;
  h.n[1] = h.n[2] = 0;
  // for ( int i = 0; i < h.N; ++i ) h.stack[0][i] = 0;
  std::fill( h.stack[0], h.stack[0]+h.N, 0 );
  std::fill( h.stack[1], h.stack[1]+h.N, 0 );
  std::fill( h.stack[2], h.stack[2]+h.N, 0 );
  for ( int i = 0; i < N; ++i ) h.stack[0][i] = N-i;
  return true;
}

bool
hanoi_check( Hanoi_status const & h ) {
  if ( h.N > N_MAX_DISK || h.N <= 0 ) {
    cerr
      << "hanoi_check, N = " << h.N
      << " deve essere <= " << N_MAX_DISK
      << " e maggiore di 0\n";
    return false;
  }
  if ( h.n[0] < 0 || h.n[1] < 0 || h.n[2] < 0 ) {
    cerr
      << "Il numero di dischi per ogni piolo deve essere >= 0"
      << "\nn1 = " << h.n[0]
      << "\nn2 = " << h.n[1]
      << "\nn3 = " << h.n[2]
      << "\n";
    return false;
  }
  if ( h.n[0]+h.n[1]+h.n[2] != h.N ) {
    cerr
      << "La somma del numero di dischi per ogni piolo deve essere = N"
      << "\nn1 = " << h.n[0]
      << "\nn2 = " << h.n[1]
      << "\nn3 = " << h.n[2]
      << "\nN  = " << h.N
      << "\n";
    return false;
  }
  std::vector<bool> disk(h.N);
  std::fill( disk.begin(), disk.end(), false );
  bool ok = true;
  for ( int np = 0; np < 3; ++np ) {
    for ( int nn = 0; ok && nn < h.n[np]; ++nn ) {
      int d = h.stack[np][nn];
      ok = d > 0 || d <= h.N;
      disk[d-1] = true;
    }
  }
  if ( !ok ) {
    cerr << "Qualche disco non è nel range [1..N]\n";
    return false;
  }
  for ( int nn = 0; ok && nn < h.N; ++nn ) ok = disk[nn];
  if ( !ok ) {
    cerr << "Qualche disco è mancante o doppio\n";
    return false;
  }
  for ( int np = 0; np < 3; ++np ) {
    for ( int nn = 1; ok && nn < h.n[np]; ++nn )
      ok = h.stack[np][nn] < h.stack[np][nn-1];
  }
  if ( !ok )
    cerr << "Qualche disco grande e' sopra un disco piu' piccolo\n";
  return ok;
}

string
disk( int N, int d ) {
  string res = "";
  for ( int i = N-d; i > 0; --i ) res += " ";
  for ( int i = 0;   i < d; ++i ) res += "o";
  res += "|" ;
  for ( int i = 0;   i < d; ++i ) res += "o";
  for ( int i = N-d; i > 0; --i ) res += " ";
  return res;
}

string
base( int N ) {
  string res = "";
  for ( int i = 2*N+1; i > 0; --i ) res += "=";
  return res;
}

void
hanoi_plot( Hanoi_status const & h ) {
  for ( int i = h.N-1; i >= 0; --i ) {
    cout
      << disk( h.N, h.stack[0][i] )
      << disk( h.N, h.stack[1][i] )
      << disk( h.N, h.stack[2][i] )
      << '\n';
  }
  cout << base(h.N) << base(h.N) << base(h.N) << '\n';
}

bool
hanoi_move( Hanoi_status & h, int from, int to, int & dm ) {
  if ( from < 1 || from > 3 ) {
    cerr << "hanoi_movel, from = " << from << " non in [1,2,3]\n";
    return false;
  }
  if ( to < 1 || to > 3 ) {
    cerr << "hanoi_movel, to = " << to << " non in [1,2,3]\n";
    return false;
  }
  if ( from == to ) {
    cerr << "hanoi_movel, from == to!\n";
    return false;
  }

  int & nf = h.n[from-1];     // alias di h.n[from-1]
  int & nt = h.n[to-1];       // alias di h.n[to-1]
  int * Sf = h.stack[from-1]; // alias di h.stack[from-1]
  int * St = h.stack[to-1];   // alias di h.stack[to-1]
  if ( nf == 0 ) {
    cerr << "from = " << from << " non trovo nessun disco!\n";
    return false;
  }
  // rimuovo disco
  --nf; dm = Sf[nf]; Sf[nf] = 0;
  if ( nt > 0 && dm > St[nt-1] ) {
    cerr
      << "muovo disco piu' grande [" << dm
      << "] su disco piu' piccolo [" << St[nt-1] << "]\n";
    return false;
  }
  St[nt] = dm;
  ++nt;
  return true;
}
