#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "course_lib.h"

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

extern void
hanoi2 (int n, const int start, const int end, const int temp, vector<int> & from, vector<int> & to)
{
    if (n==1) {
        from.push_back(start);
        to.push_back(end);
        return;
    }
    else {
        hanoi2( n-1, start, temp, end, from, to);
        from.push_back(start);
        to.push_back(end);
        hanoi2( n-1, temp, end, start, from, to);
    }
}
void hanoi( int N, vector<int> & from, vector<int> & to )
{
    hanoi2(N,1,3,2,from,to);
}
