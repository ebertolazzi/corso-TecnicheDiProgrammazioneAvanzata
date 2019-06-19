//Simone Passerini
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void order(int* vec, int sx, int dx) {
    if(sx < dx) 
    {
        int pivotValue = vec[dx],
            pivot = sx;

        for(int i = sx; i < dx; i++) 
        {
            if(vec[i] < pivotValue)
            {
                swap(vec[i], vec[pivot]);
                pivot++;
            }
        }
        swap(vec[dx], vec[pivot]);
        order(vec, sx, pivot - 1);
        order(vec, pivot + 1, dx);
    }
}  
void
ordina( int vec[], int N ) 
{
    order( vec, 0, N - 1 );
}
