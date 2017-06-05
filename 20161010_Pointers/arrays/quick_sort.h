/* quick_sort.h : simple quick sort implementation */
 
# ifndef EPITA_IP_QUICK_SORT_H_
# define EPITA_IP_QUICK_SORT_H_
 
# include <stdlib.h>
 
void quick_sort(int *begin, int *end);
int* partition(int *begin, int *end);
void swap(int *a, int *b);
void hybrid_sort(int *begin, int *end);
 
# endif /* EPITA_IP_QUICK_SORT_H_ */
