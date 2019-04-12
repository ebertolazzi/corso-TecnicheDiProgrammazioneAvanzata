/*
  Matrix Matrix multiplication routine
  
  g++ -O3 -funroll-loops -sse2 -sse3 -sse3 -ssse3 -sse4.1 mm_check.cc mm_standard.cc TimeMeter.cc 

  5 x 5 average time 0.01
  10 x 10 average time 0.004
  20 x 20 average time 0.014
  40 x 40 average time 0.099
  80 x 80 average time 0.789
  160 x 160 average time 8.526
  320 x 320 average time 70.61
  640 x 640 average time 981.838
  1280 x 1280 average time 10938.1
  2560 x 2560 average time 624531
  Time Ratio [ 10/5] = 0.4
  Time Ratio [ 20/10] = 3.5
  Time Ratio [ 40/20] = 7.07143
  Time Ratio [ 80/40] = 7.9697
  Time Ratio [ 160/80] = 10.8061
  Time Ratio [ 320/160] = 8.28173
  Time Ratio [ 640/320] = 13.9051
  Time Ratio [ 1280/640] = 11.1404
  Time Ratio [ 2560/1280] = 57.0969
*/

#include "mm.hh"

#include <stdint.h>

/*
 Indirizzamento column major

 ldA = leading dimension matrice A
 ldB = leading dimension matrice B
 ldC = leading dimension matrice C
*/

#define A(I,J) A[(I)+(J)*ldA]
#define B(I,J) B[(I)+(J)*ldB]
#define C(I,J) C[(I)+(J)*ldC]

template <typename Type>
void
mm_standard( Type const A[], unsigned ldA,
             Type const B[], unsigned ldB,
             Type       C[], unsigned ldC,
             unsigned n,
             unsigned p,
             unsigned m ) {
  for ( unsigned i = 0 ; i < n ; ++i )
    for ( unsigned j = 0 ; j < m ; ++j ) {
      C(i,j) = 0;
      for ( unsigned k = 0 ; k < p ; ++k )
        C(i,j) += A(i,k) * B(k,j) ;
    }
}

#define EXPLICIT_INSTANTIATE(T) \
template void mm_standard<T>( T const [], unsigned, \
                              T const [], unsigned, \
                              T       [], unsigned, \
                              unsigned, unsigned, unsigned ) ;

EXPLICIT_INSTANTIATE(float) ;
EXPLICIT_INSTANTIATE(double) ;
EXPLICIT_INSTANTIATE(int32_t) ;
EXPLICIT_INSTANTIATE(int64_t) ;
