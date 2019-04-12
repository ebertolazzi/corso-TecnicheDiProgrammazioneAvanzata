/*
  Matrix Matrix multiplication routine
  
  g++ -O3 -funroll-loops mm_check.cc mm_standard.cc mm_tiling.cc mm_recurr.cc TimeMeter.cc -lblas
  g++ -O3 -funroll-loops -sse2 -sse3 -sse3 -ssse3 -sse4.1 mm_check.cc mm_standard.cc mm_tiling.cc mm_recurr.cc TimeMeter.cc -framework Accelerate

time using dgemm

5 x 5 average time 0.0076ms
10 x 10 average time 0.0012ms
20 x 20 average time 0.0046ms
40 x 40 average time 0.032ms
80 x 80 average time 0.303ms
160 x 160 average time 9.2734ms
320 x 320 average time 9.183ms
640 x 640 average time 66.8882ms
1280 x 1280 average time 458.291ms
2560 x 2560 average time 3958.36ms
Time Ratio [ 10/5] = 0.157895
Time Ratio [ 20/10] = 3.83333
Time Ratio [ 40/20] = 6.95652
Time Ratio [ 80/40] = 9.46875
Time Ratio [ 160/80] = 30.6053
Time Ratio [ 320/160] = 0.990252
Time Ratio [ 640/320] = 7.28392
Time Ratio [ 1280/640] = 6.8516
Time Ratio [ 2560/1280] = 8.63722
   
 */

#include <iostream>
#include <iomanip>
#include <cstdlib> // near equivalent to <stdlib.h>  for exit, rand, ...
#include <cmath>   // near equivalent to <math.h>    for sin, cos, log, ..

#include <map>

#include "mm.hh"
#include "course_lib.h"

#define A(I,J) A[(I)+(J)*ldA]
#define B(I,J) B[(I)+(J)*ldB]
#define C(I,J) C[(I)+(J)*ldC]

using namespace std ;

// general random numer generator
template <typename U>
inline
U random() { return (U)rand()-(U)rand() ; }

// store average time using map of STL
static map<unsigned,double> averageTime ;

//
//  Fill with random value matric A (n x m)
//
template <typename Type>
static
void
fillRandom( Type A[], unsigned ldA, unsigned n, unsigned m ) {
  for ( unsigned i = 0 ; i < n ; ++i )
    for ( unsigned j = 0 ; j < m ; ++j )
      A(i,j) = random() ;
}

typedef double valueType ;
//typedef int64_t valueType ;

/*  Purpose
 *  =======
 *
 *  DGEMM  performs one of the matrix-matrix operations
 *
 *     C := alpha*op( A )*op( B ) + beta*C,
 *
 *  where  op( X ) is one of
 *
 *     op( X ) = X   or   op( X ) = X',
 *
 *  alpha and beta are scalars, and A, B and C are matrices, with op( A )
 *  an m by k matrix,  op( B )  a  k by n matrix and  C an m by n matrix.
 */

int
main() {

  TicToc tm ;
  unsigned nruns = 5;
  unsigned minsz = 5;
  unsigned maxsz = 1000;

  valueType * A = new valueType[ maxsz * maxsz ] ;
  valueType * B = new valueType[ maxsz * maxsz ] ;
  valueType * C = new valueType[ maxsz * maxsz ] ;

  for ( unsigned sz = minsz ; sz < maxsz ; sz *= 2 ) {
    unsigned ldA = sz ;
    unsigned ldB = sz ; 
    unsigned ldC = sz ;
    fillRandom( A, ldA, sz, sz ) ;
    fillRandom( B, ldB, sz, sz ) ;
    
    tm.tic() ;
    for ( unsigned k = 0 ; k < nruns ; ++k )
      mm_recurr( A, ldA, B, ldB, C, ldC, sz, sz, sz ) ;
      //mm_tiling( A, ldA, B, ldB, C, ldC, sz, sz, sz, 80 ) ;
      //mm_standard( A, ldA, B, ldB, C, ldC, sz, sz, sz ) ;
    tm.toc();
    double elapsed = tm.elapsed_ms() ;
    averageTime[sz] = elapsed / nruns ;
    cout << sz << " x " << sz << " average time " << averageTime[sz] << "ms\n" ;
  }
  
  for ( unsigned sz = 2*minsz ; sz < maxsz ; sz *= 2 )
    cout << "Time Ratio [ " << sz << "/" << sz/2 << "] = "
         << averageTime[sz] / averageTime[sz/2] << '\n' ; 

}
