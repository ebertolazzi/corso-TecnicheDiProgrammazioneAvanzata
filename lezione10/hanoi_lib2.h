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

  bool init( int N );
  bool check();
  void plot();
  bool move(int from, int to, int & dm );
} Hanoi_status;
