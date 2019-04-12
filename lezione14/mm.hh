/*
  Matrix Matrix multiplication routine
 */
 
template <typename Type>
void
mm_standard(
  Type const A[], unsigned ldA,
  Type const B[], unsigned ldB,
  Type       C[], unsigned ldC,
  unsigned n, // number of the rows of A
  unsigned p, // number of the columns of A and rows of B
  unsigned m  // number of the columns of B
              // the results is a matrix C of n rows and m co
);

template <typename Type>
void
mm_tiling( Type const A[], unsigned ldA,
  Type const B[], unsigned ldB,
  Type       C[], unsigned ldC,
  unsigned n, // number of the rows of A
  unsigned p, // number of the columns of A and rows of B
  unsigned m, // number of the columns of B
              // the results is a matrix C of n rows and m columns
  unsigned BK // block size
) ;

template <typename Type>
void
mm_recurr( Type const A[], unsigned ldA,
  Type const B[], unsigned ldB,
  Type       C[], unsigned ldC,
  unsigned n,   // number of the rows of A
  unsigned p,   // number of the columns of A and rows of B
  unsigned m    // number of the columns of B
                // the results is a matrix C of n rows and m columns
);
