/* quick_sort.c : simple quick sort implementation */
 
# include <stdlib.h>
 
# include "helper.h"
# include "quick_sort.h"


void swapp(int *a, int *b) {
    int
    c = *a;
    *a = *b;
    *b = c;
}
 
int* partition(int *begin, int *end)
{
    int*pivot = begin +(end-begin)/2;
    int pval = *pivot;
    swapp(pivot,end-1);
    for(int* steps = begin ; steps < end-1;steps ++)
    {
        if(*steps<pval)
        {
            swapp(steps,pivot);
            pivot++;
        }
    }
    swapp(pivot,end-1);
    return pivot;
}
 
void quick_sort(int *begin, int *end)
{
    if (begin  < end) {
        int *pivot = begin + (end - begin) / 2;
        pivot = partition(begin,end);
        quick_sort(begin, pivot);
        quick_sort(pivot + 1, end);
    }

}
 
void hybrid_sort(int *begin, int *end)
{
  if (end - begin < 2 || array_is_sorted(begin, end))
    return;
  quick_sort(begin, end);
}
