/*\
:|:
:|: Questo file contiene le funzioni e i programmi
:|: di utilita' usati nel corso
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi e prof. Andrea Del Prete
:|:
:|: ATTENZIONE per compilare questo file serve
:|: attivare C++11
:|:
:|: clang++ -std=c++-11 -stdlib=libc++ ....
:|: g++     -std=c++-11 -stdlib=libc++ ....
:|:
\*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

static
unsigned
isAvailable(
  unsigned puzzle[][9],
  unsigned row,
  unsigned col,
  unsigned num
) {
  unsigned rowStart = (row/3) * 3;
  unsigned colStart = (col/3) * 3;
  unsigned i, j;

  for ( i=0; i<9; ++i) {
    if (puzzle[row][i] == num) return 0;
    if (puzzle[i][col] == num) return 0;
    if (puzzle[rowStart + (i%3)][colStart + (i/3)] == num) return 0;
  }
  return 1;
}

static
unsigned
fillSudoku(
  unsigned puzzle[][9],
  unsigned row,
  unsigned col
) {
  unsigned i;
  if ( row<9 && col<9 ) {
    if (puzzle[row][col] != 0) {
      if ((col+1)<9) return fillSudoku(puzzle, row, col+1);
      else if((row+1)<9) return fillSudoku(puzzle, row+1, 0);
      else return 1;
    } else {
      for (i=0; i<9; ++i) {
        if ( isAvailable(puzzle, row, col, i+1) ) {
          puzzle[row][col] = i+1;
          if ( (col+1) < 9 ) {
            if (fillSudoku(puzzle, row, col +1)) return 1;
            else puzzle[row][col] = 0;
          } else if ( (row+1) < 9 ) {
            if ( fillSudoku(puzzle, row+1, 0) ) return 1;
            else puzzle[row][col] = 0;
          } else {
            return 1;
          }
        }
      }
    }
    return 0;
  } else {
    return 1;
  }
}

void
sodoku( unsigned board[9][9] ) {
  fillSudoku(board, 0, 0);
}
