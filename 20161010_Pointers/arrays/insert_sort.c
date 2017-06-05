#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "insert_sort.h"

int*binary_search(int*begin,int*end,int x);


// insert using the naive algo
void array_insert(int *begin, int *end, int x)
{
	if (x > *(end-1)) 
	{
		*end = x;
	}
	else 
	{
		while (x<*(end-1) && end-1 > begin)
		{
			*end = *(end-1);
			end--;
		}
	*end = x;
	}
}
 
// insert using binary search
void array_insert_bin(int *begin, int *end, int x)
{
    int *case_stop  = binary_search(begin,end , x );
    while (end-1 > case_stop)
    {
        *end = *(end-1);
        end--;
    }
    *end = x;
    
}
// insertion sort using naive method
void array_insert_sort(int *begin, int *end)
{
	for (;begin<end;begin++)
	{
	   array_insert(0,begin,*begin);
	}
}

int* binary_search(int*begin,int*end,int x)
{	
	int *mid = NULL;
    while (end-begin > 0)
	{
        mid = begin + (end -begin)/2;
		if (x<*mid)
		{
			end = mid;
		}
		else if (x>*mid)
		{
			begin= mid + 1;
		}
		else
		{
			return mid;
		}
	}

	return mid;


}

// insertion sort using binary search
void array_insert_sort_bin(int *begin, int *end)
{


  for (;begin<end;begin++)
	{
	   array_insert_bin(0,begin,*begin);
	}

}
