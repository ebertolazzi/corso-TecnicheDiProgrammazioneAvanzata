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

#include "hanoi_lib3.h"

#include <iostream>
#include <iomanip> // per setw
#include <algorithm> // per std::swap
#include <string> // per std::swap
#include <vector>

using namespace std;

Hanoi_status::Hanoi_status() {
  cout << "Passo dal costruttore\n";
  this->N    =
  this->n[0] =
  this->n[1] =
  this->n[2] = 0;
  std::fill( this->stack[0], this->stack[0]+N_MAX_DISK, 0 );
  std::fill( this->stack[1], this->stack[1]+N_MAX_DISK, 0 );
  std::fill( this->stack[2], this->stack[2]+N_MAX_DISK, 0 );
}

Hanoi_status::Hanoi_status( int N ) {
  cout << "Passo dal costruttore 2\n";
  this->init(N);
}

Hanoi_status::~Hanoi_status() {
  cout << "Passo dal distruttore\n";
}

/*
  Definisco "metoto" init della struttura Hanoi_status
  :: operatore di "scopo"
*/
bool
Hanoi_status::init( int N ) {
  if ( N > N_MAX_DISK || N <= 0 ) {
    cerr
      << "hanoi_init, N = " << N
      << " deve essere <= " << N_MAX_DISK
      << " e maggiore di 0\n";
    return false;
  }
  this->N    = this->n[0] = N;
  this->n[1] = this->n[2] = 0;
  // for ( int i = 0; i < this->N; ++i ) this->this->this->stack[0][i] = 0;
  std::fill( this->stack[0], this->stack[0]+this->N, 0 );
  std::fill( this->stack[1], this->stack[1]+this->N, 0 );
  std::fill( this->stack[2], this->stack[2]+this->N, 0 );
  for ( int i = 0; i < this->N; ++i ) this->stack[0][i] = this->N-i;
  return true;
}

bool
Hanoi_status::check() {
  if ( this->N > N_MAX_DISK || this->N <= 0 ) {
    cerr
      << "hanoi_check, N = " << this->N
      << " deve essere <= " << N_MAX_DISK
      << " e maggiore di 0\n";
    return false;
  }
  if ( this->n[0] < 0 || this->n[1] < 0 || this->n[2] < 0 ) {
    cerr
      << "Il numero di dischi per ogni piolo deve essere >= 0"
      << "\nn1 = " << this->n[0]
      << "\nn2 = " << this->n[1]
      << "\nn3 = " << this->n[2]
      << "\n";
    return false;
  }
  if ( this->n[0]+this->n[1]+this->n[2] != this->N ) {
    cerr
      << "La somma del numero di dischi per ogni piolo deve essere = N"
      << "\nn1 = " << this->n[0]
      << "\nn2 = " << this->n[1]
      << "\nn3 = " << this->n[2]
      << "\nN  = " << this->N
      << "\n";
    return false;
  }
  std::vector<bool> disk(this->N);
  std::fill( disk.begin(), disk.end(), false );
  bool ok = true;
  for ( int np = 0; np < 3; ++np ) {
    for ( int nn = 0; ok && nn < this->n[np]; ++nn ) {
      int d = this->stack[np][nn];
      ok = d > 0 || d <= this->N;
      disk[d-1] = true;
    }
  }
  if ( !ok ) {
    cerr << "Qualche disco non è nel range [1..N]\n";
    return false;
  }
  for ( int nn = 0; ok && nn < this->N; ++nn ) ok = disk[nn];
  if ( !ok ) {
    cerr << "Qualche disco è mancante o doppio\n";
    return false;
  }
  for ( int np = 0; np < 3; ++np ) {
    for ( int nn = 1; ok && nn < this->n[np]; ++nn )
      ok = this->stack[np][nn] < this->stack[np][nn-1];
  }
  if ( !ok )
    cerr << "Qualche disco grande e' sopra un disco piu' piccolo\n";
  return ok;
}

static
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

static
string
base( int N ) {
  string res = "";
  for ( int i = 2*N+1; i > 0; --i ) res += "=";
  return res;
}

void
Hanoi_status::plot() {
  for ( int i = this->N-1; i >= 0; --i ) {
    cout
      << disk( this->N, this->stack[0][i] )
      << disk( this->N, this->stack[1][i] )
      << disk( this->N, this->stack[2][i] )
      << '\n';
  }
  cout << base(this->N) << base(this->N) << base(this->N) << '\n';
}

bool
Hanoi_status::move( int from, int to, int & dm ) {
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

  int & nf = this->n[from-1];     // alias di this->n[from-1]
  int & nt = this->n[to-1];       // alias di this->n[to-1]
  int * Sf = this->stack[from-1]; // alias di this->stack[from-1]
  int * St = this->stack[to-1];   // alias di this->stack[to-1]
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
