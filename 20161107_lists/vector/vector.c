/* vector.h : Simple vector implementation */
 
# ifndef VECTOR_H_
# define VECTOR_H_
 
# include <stdlib.h>
#include<assert.h>
#include <stdio.h>
 
/*struct vector {;
 
  size_t        capacity, size;
  int          *data;
 };
 */
 
/*
 * vector_make(capacity) create an empty vector
 * with initial storage size capacity
 */
struct vector* vector_make(size_t capacity)
{
    struct vector *vector;
    vector->capacity = capacity;
    vector->size = 0;
    return vector;
    
}

int double_vector_size(struct vector *vect)
{
    int *tmp = realloc(vect->data, 2 * vect->capacity * sizeof (int));
    if (tmp == NULL) {
        // oups no more memory ?
        warn("realloc of data fails");
        return 0;
    }
    vect->data = tmp;
    vect->capacity *= 2;
    return 1;
}
 
/*
 * vector_push_back(vect, x) add x at the end of vect
 * if vect is full increase capacity
 */
void vector_push_back(struct vector *vect, int x)
{
    size_t i = 0;
    for( i; i < vect->size && *(vect->data+i);++i)
    {
        continue;
    }
    if (i == vect->size)
    {
        double_vector_size(vect);
    }
    vect->size +=1;
    vect->*(data+i) = x;
    
    
}
 
/*
 * vector_pop_back(vect, &x) get the last element of vect
 * remove the element
 * store result in x
 * return true (!=0) if size > 0
 * return false (0) otherwise
 */
int  vector_pop_back(struct vector *vect, int *x)
{
    for(;*(vect->data);++vect->data)
    {
        continue;
    }
    vect->data = NULL;
    vect->size -=1;
    return (vect->size >0);
}
 
/*
 * vector_push_front(vect, x) add x at the beginning of vect
 * if vect is full increase capacity
 */
void vector_push_front(struct vector *vect, int x)
{
    if (vect->size == vect->capacity)
    {
        vect->capacity +=1;
        double_vector_size (vect)}
    int*data1 = vect->data;
    vect->*(data) = x;
    vect -> data +1 = data1;
    
}
 
/*
 * vector_pop_back(vect, &x) get the first element of vect
 * remove the element
 * store result in x
 * return true (!=0) if size > 0
 * return false (0) otherwise
 */
int  vector_pop_front(struct vector *vect, int *x)
{
    x = vect->data;
    vect->data=vect->data+1;
    vect->size -=1;
    return (vect->size >0);
}
 
/*
 * vector_insert_at(vect, pos, x) add x in pos cell of vect
 * return true (!=0) if pos <= size of vect
 * return false (0) otherwise
 * vector_insert_at(v, v->size, x) is equivalent to vector_push_back(v, x)
 * vector_insert_at(v, 0, x) is equivalent to vector_push_front(v, x)
 * if vect is full increase capacity
 */
int vector_insert_at(struct vector *vect, size_t pos, int x)
{
    if (vect->size ==0  || pos >vect->size)
    {
        return 0;
    }
    vector_push_front(vect+pos,x);
    return 1;
}
 
/*
 * vector_extract_at(vect, pos, &x) get the pos element of vect
 * remove the element
 * store result in x
 * return false (0) if size == 0 or pos >= size
 * vector_extract_at(v, v->size - 1, &x) is equivalent to vector_pop_back(v, &x)
 * vector_extract_at(v, 0, &x) is equivalent to vector_pop_front(v, &x)
 */
int vector_extract_at(struct vector *vect, size_t pos, int *x)
{
    if(vect->size ==0 || vect->size<pos)
    {
        return 0;
    }
    if (pos== 0)
    {
        vector_pop_front(v,&x);
    }
    if (pos == vect->size -1)
    {
        vector_pop_back(v,&x);
    }
    else
    {
        vector_pop_front(vect +pos,&x);
    }
    return 1;
}
 
/*
 * vector_clone(vect) create a complete copy of vect
 * both storage contains the same elements but are not at the same memory place
 */
struct vector* vector_clone(struct vector *vect){
    struct vector *clone;
    vector_make(vect->capacity);
    for(;vect->data;++vect->data)
    {
        clone ->data = vect->data;
        clone->data ++ ;
    }
    return clone;
}
