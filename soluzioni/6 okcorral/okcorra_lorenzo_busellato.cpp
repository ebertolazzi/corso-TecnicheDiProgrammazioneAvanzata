#include <algorithm>

//Sorts subarray vec[lo:hi] with insertion sort
void insertionSort(int v[], int lo, int hi) {
	for(int i = lo + 1; i < hi; ++i)
		for(int j = i - 1; j >= lo && v[j] > v[j + 1]; --j)
            std::swap(v[j], v[j + 1]);
}

//Finds the median of three values
int median3(int* vec, int i, int j, int k) {
    return(vec[i] < vec[j]) ?
           ((vec[j] < vec[k]) ? j : (vec[i] < vec[k]) ? k : i) :
           ((vec[k] < vec[j]) ? j : (vec[k] < vec[i]) ? k : i);
}

//partitions the subarray vec[lo:hi] with the median3 as pivot
int pivot(int* vec, int lo, int hi) {
    int m = median3(vec, lo, lo + (hi - lo + 1)/2, hi);

    std::swap(vec[m], vec[lo]);

    int i = lo,
        j = hi + 1,
        v = vec[lo];
    // a[lo] is unique largest element
    while (vec[++i] < v) {
        if (i == hi) { std::swap(vec[lo], vec[hi]); return hi; }
    }
    // a[lo] is unique smallest element
    while (v < vec[--j])
        if (j == lo + 1)
            return lo;
    // the main loop
    while (i < j) {
        std::swap(vec[i], vec[j]);
        while (vec[++i] < v) ;
        while (v < vec[--j]) ;
    }
    // put partitioning item v at a[j]
    std::swap(vec[lo], vec[j]);
    // now, a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
    return j;
}

//Sorts the array using insertion sort when the subarray is less than insertionCutoff in size, or quicksort with median3 as pivot if it's bigger
void quickX(int* vec, int lo, int hi) {
    if(hi <= lo) return;
    if((hi - lo + 1) <= 8) {
        insertionSort(vec, lo, hi + 1);
        return;
    }
    int j = pivot(vec, lo, hi);
    quickX(vec, lo, j - 1);
    quickX(vec, j + 1, hi);
}

void
ordina( int vec[], int N ) {
  quickX( vec, 0, N - 1 );
}
