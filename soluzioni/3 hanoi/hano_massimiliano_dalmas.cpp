#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

//#include "course_lib.h"

using namespace std;

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
hanoi_plot(
  int N,
  int A[],
  int B[],
  int C[],
  ostream & stream
) {
  for ( int i = N-1; i >= 0; --i ) {
    stream
      << disk( N, A[i] )
      << disk( N, B[i] )
      << disk( N, C[i] )
      << '\n';
  }
  stream << base(N) << base(N) << base(N) << '\n';
}

static void 
__hanoi(int N, 
        int A, int B, int C, 
        vector<int> & from, 
        vector<int> & to)
{
  if (N > 1){
    __hanoi(N - 1,A,C,B,from,to);
    from.push_back(A);
    to.push_back(C);
    __hanoi(N - 1,B,A,C,from,to);
  } else {
    from.push_back(A);
    to.push_back(C);
  }
}

void
hanoi( int N, vector<int> & from, vector<int> & to ) {
  __hanoi(N,1,2,3,from,to);
}
