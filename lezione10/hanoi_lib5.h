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
#include <vector>

using namespace std;

class Hanoi_status {
private: // ridondante, private è il default
  int N;    // 4
  int n[3]; // 12
  int * stack[3];

public:

  // costruttore di default
  Hanoi_status();

  // costruttore alternativo
  Hanoi_status( int N );

  // distruttore
  ~Hanoi_status();

  bool init( int N );
  bool check();
  void plot();
  bool move(int from, int to, int & dm );
};
