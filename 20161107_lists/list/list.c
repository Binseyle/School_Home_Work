 /* Linked lists */
#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include <assert.h>
/* Simply linked list of integers */
 
 
/*
 * Standard operations
 * We're working with sentinels and external allocation
 * This means that our lists always have a fake head (the sentinel)
 * and all allocations (and free) are performed by the caller, not the operation
 */
 
/*
 * list_init(list)
 * initialise the sentinel node list
 */
void list_init(struct list *list)
{
    list->next = NULL;
    
}
 
/*
 * list_is_empty(list)
 * returns true if the list is empty
 * remember, we have a sentinel thus a list always has at least one node,
 * the list is empty if this node doesn't have a next.
 */

int list_is_empty(struct list *list)
{
    if(list->next->next == NULL)
    {
        return 1;
    }
    return 0;
}
 
/*
 * list_len(list)
 * returns the length of the list (don't count the sentinel)
 */
size_t list_len(struct list *list)
{
    size_t res = 0;
    list =  list->next;
    while(list != NULL)
    {
        res ++;
        list = list->next;
 }
 return res;
}
 
/*
 * list_push_front(list, elm)
 * attach elm in front of list, that is after the sentinel.
 * Note that elm is already a node, you just have to attach it.
 */
void list_push_front(struct list *list, struct list *elm)
{
    struct list *tail = list ->next;
    elm -> next = tail ;
    list ->next  = elm;
    
}
 
/*
 * list_pop_front(list)
 * Extract the first element (not the sentinel) of list.
 * This operation detaches the element from the list and returns it (caller is
 * responsible for freeing it.)
 * If the list is empty, the function returns NULL.
 */
struct list* list_pop_front(struct list *list)
{
    struct list *pop =  NULL;
    if (list->next)
    {
        pop = list -> next ;
        list-> next =  list ->next->next;
    }
    return pop;
}

 
/*
 * list_find(list, value)
 * search for the first node containing value and returns (without detaching it)
 * the corresponding list node. The function returns NULL if the value is not
 * present in the list.
 */
struct list* list_find(struct list *list, int value)
{
    for (;list && list->data !=value;list = list->next ){continue;}
    
    return list;
}
 
/*
 * list_is_sorted(list)
 * check whether the list is sorted in increasing order
 */
int list_is_sorted(struct list *list)
{
    for(;list->next ;list =list->next)
    {
        if(list -> data  > list->next->data)
        {
            return 0;
        }
    }
    return 1;
}
 
/*
 * list_insert(list, elm)
 * insert elm in the sorted list (keeping the list sorted)
 * Like list_push_front, elm is already a list node.
 */
void list_insert(struct list *list, struct list *elm)
{
	for(;list && list->data < elm->data;list = list->next)
	{	
		continue;
	}
	elm->next = list->next;
	list->next = elm;
}
 
/*
 * More algorithms
 */
 
/*
 * list_rev(list)
 * reverse the list using the same nodes (just move them) and the same sentinel.
 */
void list_rev(struct list *list)
{
    struct list *chap = list->next;
    if(chap->next)
    {
        chap = chap->next;
        struct list *save = chap;
        list->next->next = NULL;
        for(;save; chap = save)
        {
            save = chap->next;
            list_push_front(list,chap);
            
        }
    }
 }
/*
 * list_half_split(list, second)
 * split the list in half and put the second half in second
 * second is an empty list (just a sentinel)
 */
 void list_half_split(struct list *list, struct list *second)
    {
        struct list *x = list;
        struct list *deuxx =list->next;
        for(;deuxx;x = x->next)
        {
            deuxx = deuxx->next;
            if(deuxx)
                deuxx = deuxx->next;
        }
        list_init(second);
        second->next = x->next;
        x->next = NULL;
    }

void print_list(struct list *list)
{
    int line = 1;
    printf("[");
    if (list->next) {
        goto pastfst;
        while (list->next) {
            line += printf(";");
            if (line > 72) {
                printf("\n ");
                line = 1;
            }
        pastfst:
            line += printf(" %d", list->next->data);
            list = list->next;
        }
    }
    printf(" ]\n");
}

void list_insert_sort(struct list *list)
{
    if (list_is_empty(list))        // nothing to do
        return;
        struct list fake_head = {0,0}; // temporary head
        while (!list_is_empty(list)) {
            struct list *elm = list_pop_front(list);
            list_insert(&fake_head, elm);
        }
        list->next = fake_head.next;   // reattach the sorted list to its sentinel
}
int main(void)
{
    struct list *list =malloc(sizeof( struct list));
    list_init(list);
    print_list(list);
    //assert(list_is_empty(list));
    for(int i = 0 ; i<20;++i)
    {
        struct list *tmp = malloc(sizeof(struct list));
        tmp->data =i ;
        tmp->next = NULL;
        list_push_front(list,tmp);
        //assert(list->next->data == i);
    }
    
    print_list(list);
    printf("Inversion de la liste \n");
    list_rev(list);
    print_list(list);
    assert(list_len(list)==20);
    struct list *tmp = malloc(sizeof(struct list));
    tmp->data =20 ;
    tmp->next = NULL;
    
    list_insert(list,tmp);
    print_list(list);
    list_init(list);
    print_list(list);
    return 0;
}
