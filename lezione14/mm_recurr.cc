/*
  Matrix Matrix multiplication routine
  
 */

#include "mm.hh"
#include <algorithm>

#define A(I,J) A[(I)+(J)*ldA]
#define B(I,J) B[(I)+(J)*ldB]
#define C(I,J) C[(I)+(J)*ldC]

template <typename Type>
inline
void
mm_base_addto4x4( Type const A[], unsigned ldA,
                  Type const B[], unsigned ldB,
                  Type       C[], unsigned ldC ) {
  for ( unsigned i = 0 ; i < 4 ; ++i )
    for ( unsigned j = 0 ; j < 4 ; ++j ) {
      Type tmp = 0 ;
      for ( unsigned k = 0 ; k < 4 ; ++k ) tmp += A(i,k) * B(k,j) ;
      C(i,j) += tmp ;
    }
}

template <typename Type>
inline
void
mm_base_addto8x8( Type const A[], unsigned ldA,
                  Type const B[], unsigned ldB,
                  Type       C[], unsigned ldC ) {
  for ( unsigned i = 0 ; i < 8 ; i += 4 )
    for ( unsigned j = 0 ; j < 8 ; j += 4 )
      for ( unsigned k = 0 ; k < 8 ; k += 4 )
        mm_base_addto4x4( &A(i,k), ldA, &B(k,j), ldB, &C(i,j), ldC ) ;
}

template <typename Type>
inline
void
mm_base_addto16x16( Type const A[], unsigned ldA,
                    Type const B[], unsigned ldB,
                    Type       C[], unsigned ldC ) {
  for ( unsigned i = 0 ; i < 16 ; i += 8 )
    for ( unsigned j = 0 ; j < 16 ; j += 8 )
      for ( unsigned k = 0 ; k < 16 ; k += 8 )
        mm_base_addto8x8( &A(i,k), ldA, &B(k,j), ldB, &C(i,j), ldC ) ;
}

template <typename Type>
inline
void
mm_classin_addto( Type const A[], unsigned ldA,
                  Type const B[], unsigned ldB,
                  Type       C[], unsigned ldC,
                  unsigned n,
                  unsigned p,
                  unsigned m ) {
  for ( unsigned i = 0 ; i < n ; ++i )
    for ( unsigned j = 0 ; j < m ; ++j ) {
      Type tmp = 0 ;
      for ( unsigned k = 0 ; k < p ; ++k ) tmp += A(i,k) * B(k,j) ;
      C(i,j) += tmp ;
    }
}

template <typename Type>
inline
void
mm_base_addto( Type const A[], unsigned ldA,
               Type const B[], unsigned ldB,
               Type       C[], unsigned ldC,
               unsigned n,
               unsigned p,
               unsigned m ) {
  unsigned const NB = 16 ;
  for ( unsigned jj = 0 ; jj < m ; jj += NB ) {
    unsigned column = std::min(NB,m-jj) ;
    for ( unsigned ii = 0 ; ii < n ; ii += NB ) {
      unsigned row = std::min(NB,n-ii) ;
      for ( unsigned kk = 0 ; kk < p ; kk += NB ) {
        unsigned rc = std::min(NB,p-kk) ;
        if ( row == NB && rc == NB && column == NB )
          mm_base_addto16x16( &A(ii,kk), ldA,
                              &B(kk,jj), ldB,
                              &C(ii,jj), ldC ) ;
        else
          mm_classin_addto( &A(ii,kk), ldA,
                            &B(kk,jj), ldB,
                            &C(ii,jj), ldC,
                            row, rc, column ) ;
      }
    }
  }
}

//! C += A*B
template <typename Type>
void
mm_recurr_addto( Type const A[], unsigned ldA,
                 Type const B[], unsigned ldB,
                 Type       C[], unsigned ldC,
                 unsigned n,
                 unsigned p,
                 unsigned m ) {
                 
  unsigned const NB = 400 ; 
  if ( n <= NB && p <= NB && m <= NB ) {
    mm_base_addto( A, ldA, B, ldB, C, ldC, n, p, m ) ;
    return ;
  }

  /*
  //  splitting tipo 1A
  //  +-------+    +-------+ +-------+
  //  |       |    |       | |       |
  //  |  C11  |    |  A11  | |  B11  |
  //  |       |    |       | |       |
  //  +-------+ += +-------+ +-------+
  //  |       |    |       |
  //  |  C21  |    |  A21  |
  //  |       |    |       |
  //  +-------+    +-------+
  //
  //  splitting tipo 1B
  //  +-------+    +-------+-------+ +-------+
  //  |       |    |       |       | |       |
  //  |  C11  |    |  A11  |  A12  | |  B11  |
  //  |       |    |       |       | |       |
  //  +-------+ += +-------+-------+ +-------+
  //  |       |    |       |       | |       |
  //  |  C21  |    |  A21  |  A22  | |  B21  |
  //  |       |    |       |       | |       |
  //  +-------+    +-------+-------+ +-------+
  //
  //  splitting tipo 2A
  //  +-------+-------+    +-------+ +-------+-------+
  //  |       |       |    |       | |       |       |
  //  |  C11  |  C12  | += |  A11  | |  B11  |  B12  |
  //  |       |       |    |       | |       |       |
  //  +-------+-------+    +-------+ +-------+-------+
  //
  //  splitting tipo 2B
  //  +-------+-------+    +-------+-------+ +-------+-------+
  //  |       |       |    |       |       | |       |       |
  //  |  C11  |  C12  | += |  A11  |  A12  | |  B11  |  B12  |
  //  |       |       |    |       |       | |       |       |
  //  +-------+-------+    +-------+-------+ +-------+-------+
  //                                         |       |       |
  //                                         |  B21  |  B22  |
  //                                         |       |       |
  //                                         +-------+-------+
  //
  //  splitting tipo 3A
  //  +------+-------+    +-------+ +-------+-------+
  //  |      |       |    |       | |       |       |
  //  |  C11 |  C12  |    |  A11  | |  B11  |  B12  |
  //  |      |       |    |       | |       |       |
  //  +------+-------+ += +-------+ +-------+-------+
  //  |      |       |    |       |
  //  |  C21 |  C22  |    |  A21  |
  //  |      |       |    |       |
  //  +------+-------+    +-------+
  //
  //  splitting tipo 3B
  //  +-------+-------+    +-------+-------+ +-------+-------+
  //  |       |       |    |       |       | |       |       |
  //  |  C11  |  C12  |    |  A11  |  A12  | |  B11  |  B12  |
  //  |       |       |    |       |       | |       |       |
  //  +-------+-------+ += +-------+-------+ +-------+-------+
  //  |       |       |    |       |       | |       |       |
  //  |  C21  |  C22  |    |  A21  |  A22  | |  B21  |  B22  |
  //  |       |       |    |       |       | |       |       |
  //  +-------+-------+    +-------+-------+ +-------+-------+
  //
  */
  
  unsigned n2 = n/2 ;
  unsigned m2 = m/2 ;
  unsigned p2 = p/2 ;

  // n x p
  Type const * A11 = A ;
  Type const * A12 = A   + ldA * p2 ;
  Type const * A21 = A   + n2       ;
  Type const * A22 = A12 + n2       ;
 
  // p x m
  Type const * B11 = B ;
  Type const * B12 = B   + ldB * m2 ;
  Type const * B21 = B   + p2 ;
  Type const * B22 = B12 + p2 ;

  // n x m
  Type       * C11 = C ;
  Type       * C12 = C   + ldC * m2 ;
  Type       * C21 = C   + n2 ;
  Type       * C22 = C12 + n2 ;

  // matrix C is n x m
  if ( 2*n > 3*m ) { // matrix is tall 
    if ( 2*n > 3*p ) { // splitting of type 1A
      mm_recurr_addto( A11, ldA, B11, ldB, C11, ldC, n2,   p, m ) ;
      mm_recurr_addto( A21, ldA, B11, ldB, C21, ldC, n-n2, p, m ) ;
    } else {  // splitting of type 1B
      mm_recurr_addto( A11, ldA, B11, ldB, C11, ldC, n2,   p2,   m ) ;
      mm_recurr_addto( A12, ldA, B21, ldB, C11, ldC, n2,   p-p2, m ) ;

      mm_recurr_addto( A21, ldA, B11, ldB, C21, ldC, n-n2, p2,   m ) ;
      mm_recurr_addto( A22, ldA, B21, ldB, C21, ldC, n-n2, p-p2, m ) ;
    }
  } else if ( 3*n < 2*m ) { // matrix is flat
    if ( 2*p > 3*n ) { // splitting of type 2B
      mm_recurr_addto( A11, ldA, B11, ldB, C11, ldC, n, p2,   m2 ) ;
      mm_recurr_addto( A12, ldA, B21, ldB, C11, ldC, n, p-p2, m2 ) ;

      mm_recurr_addto( A11, ldA, B12, ldB, C12, ldC, n, p2,   m-m2 ) ;
      mm_recurr_addto( A12, ldA, B22, ldB, C12, ldC, n, p-p2, m-m2 ) ;
    } else { // splitting of type 2A
      mm_recurr_addto( A11, ldA, B11, ldB, C11, ldC, n, p, m2   ) ;
      mm_recurr_addto( A11, ldA, B12, ldB, C12, ldC, n, p, m-m2 ) ;    
    }
  } else {
    if ( 2*n > 3*p ) { // splitting of type 3A
      mm_recurr_addto( A11, ldA, B11, ldB, C11, ldC, n2,   p, m2   ) ;
      mm_recurr_addto( A11, ldA, B12, ldB, C12, ldC, n2,   p, m-m2 ) ;

      mm_recurr_addto( A21, ldA, B11, ldB, C21, ldC, n-n2, p, m2   ) ;
      mm_recurr_addto( A21, ldA, B12, ldB, C22, ldC, n-n2, p, m-m2 ) ;
    } else { // splitting of type 3B
      mm_recurr_addto( A11, ldA, B11, ldB, C11, ldC, n2,   p2,   m2   ) ;
      mm_recurr_addto( A12, ldA, B21, ldB, C11, ldC, n2,   p-p2, m2   ) ;

      mm_recurr_addto( A11, ldA, B12, ldB, C12, ldC, n2,   p2,   m-m2 ) ;
      mm_recurr_addto( A12, ldA, B22, ldB, C12, ldC, n2,   p-p2, m-m2 ) ;

      mm_recurr_addto( A21, ldA, B11, ldB, C21, ldC, n-n2, p2,   m2   ) ;
      mm_recurr_addto( A22, ldA, B21, ldB, C21, ldC, n-n2, p-p2, m2   ) ;

      mm_recurr_addto( A21, ldA, B12, ldB, C22, ldC, n-n2, p2,   m-m2 ) ;
      mm_recurr_addto( A22, ldA, B22, ldB, C22, ldC, n-n2, p-p2, m-m2 ) ;    
    }

  }
}

////////////////////////////////////////////////////////////////////////////////

template <typename Type>
void
mm_recurr( Type const A[], unsigned ldA,
           Type const B[], unsigned ldB,
           Type       C[], unsigned ldC,
           unsigned n,
           unsigned p,
           unsigned m ) {

  for ( unsigned i = 0 ; i < n ; ++i )
    for ( unsigned j = 0 ; j < m ; ++j )
      C(i,j) = 0 ;

  mm_recurr_addto( A, ldA, B, ldB, C, ldC, n, p, m ) ;
}

#define EXPLICIT_INSTANTIATE(T) \
template void mm_recurr<T>( T const [], unsigned, \
                            T const [], unsigned, \
                            T       [], unsigned, \
                            unsigned, unsigned, unsigned ) ; \
template void mm_recurr_addto<T>( T const [], unsigned, \
                                  T const [], unsigned, \
                                  T       [], unsigned, \
                                  unsigned, unsigned, unsigned )

EXPLICIT_INSTANTIATE(float) ;
EXPLICIT_INSTANTIATE(double) ;
EXPLICIT_INSTANTIATE(int32_t) ;
EXPLICIT_INSTANTIATE(int64_t) ;
