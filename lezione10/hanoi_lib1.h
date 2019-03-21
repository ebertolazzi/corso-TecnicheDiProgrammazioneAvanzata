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

#include <iostream>
#include <iomanip> // per setw
#include <algorithm> // per std::swap

using namespace std;

#define N_MAX_DISK 30

/*
struct Hanoi_status_ {
  int N;
  int n[3];
  int stack[3][N_MAX_DISK];
};

typedef struct Hanoi_status_ Hanoi_status;
*/

typedef struct {
  int N; // 4
  int n[3]; // 12
  int stack[3][N_MAX_DISK]; // 360
} Hanoi_status;

bool
hanoi_init( Hanoi_status & h, int N );

bool
hanoi_check( Hanoi_status const & h );

void
hanoi_plot( Hanoi_status const & h );

bool
hanoi_move( Hanoi_status & h, int from, int to, int & dm );
