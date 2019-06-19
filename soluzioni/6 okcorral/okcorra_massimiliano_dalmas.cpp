#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits.h>

#include "course_lib.h"

using namespace std;

#define SWAP(a,b)              \
do {                           \
    auto tmp = *(a);           \
    *(a) = *(b);               \
    *(b) = tmp;                \
} while (0)

#define DEBUG      0
#define MAX_THRESH 50
#define STACK_SIZE (static_cast<size_t>(log(INT_LEAST32_MAX))    )
#define PUSH(a,b)  ((void)((lst->lo = a), (lst->hi = b), (++lst)))
#define POP(a,b)   ((void)((--lst),(a = lst->lo),(b = lst->hi))  )
#define STACK_NOT_EMPTY (stack < lst)

template<typename T>
struct stack_frame
{
    T *lo;
    T *hi;
};

template<typename T>
using stack_frame_t = struct stack_frame<T>;


void ordina( int * const ary, int size ) {
    int *base_ptr = ary;

    if (size == 0) return;

    stack_frame_t<int> stack[STACK_SIZE];// = new stack_frame_t<T>[STACK_SIZE];
    stack_frame_t<int> *lst = stack;
    auto low  = base_ptr;
    auto high = base_ptr + (size - 1);

    PUSH(NULL,NULL); 

    while (STACK_NOT_EMPTY)
    {
        // Select median value
        auto mid = low + ((high - low) >> 1);
        #if DEBUG
            if ((stack + STACK_SIZE - 1) < lst)
                cout << "STACK OVERFLOW!" << endl;
            if  (stack > lst)
                cout << "STACK UNDERFLOW" << endl;
            if ((mid < base_ptr) || (mid > (base_ptr +(size - 1))))
                cout << "MID OUT" << endl;
            if ((low < base_ptr) || (low > (base_ptr +(size - 1))))
                cout << "LOW OUT" << endl;
            if ((high < base_ptr) || (high > (base_ptr +(size - 1))))
                cout << "HI OUT" << endl;
        #endif 
        //cout << *low << " " << *mid << " " << *high << endl;
        if (*mid < *low)
            SWAP(mid,low);
        if (*high < *mid)
        {
            SWAP(high,mid);
            if (*mid < *low)
                SWAP(mid,low);
        }
        auto left  = low + 1;
        auto right = high - 1;
        do {
            // swapping around pivot
            while (*left < *mid)
                left++; 
            while (*mid < *right)
                right--;
            if (left < right)
            {
                SWAP(left,right);
                if (left == mid)
                    mid = right;
                else if (mid == right)
                    mid = left;
                left++;
                right--;
            } else if (left == right) {
                left++;
                right--;
                break;
            }
        } while (left <= right);

        // stack based 'recursion'
        if (right - low <= MAX_THRESH)
        {      
            if (high - left <= MAX_THRESH)      
                POP(low,high);
            else
                low = left;
        }
        else if (high - left <= MAX_THRESH)
            high = right;
        else if ((right - low) > (high - left))
        {
            PUSH(low,right);
            low = left;
        } else {
            PUSH(left,high);
            high = right;
        }
    }

    high = base_ptr + (size - 1);
    for (low = base_ptr + 1;low <= high ; low++)
    {
        auto aux = low;
        while ((*(aux - 1) > *aux) && (aux > base_ptr))
        {
            SWAP((aux-1),aux);
            aux--;
        }  
    }
    //delete stack;
}
