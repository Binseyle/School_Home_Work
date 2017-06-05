/* queue.h: dynamic queue */
/*
 * queue_init(queue) initialize an empty queue container
 * allocation of the container is kept external for more flexibility
 *
 /
*/

# include <stdio.h>
# include <stdlib.h>
# include "queue.h"

void queue_init(struct queue *queue)
{
	queue->store = NULL;
	queue->size =0;
}
 

// queue_is_empty(queue) test for emptyness
 
int queue_is_empty(struct queue *queue)
{
	return(queue->store == NULL);
}
 
/*
 * queue_push(queue, elm) push elm
 */
void queue_push(struct queue *queue, void *elm)
{
    struct queue *tmp;
    tmp= malloc(sizeof(struct queue));
     tmp -> value = *elm;
     if (queue != NULL)
     {
     	tmp->next = queue ->next;
	q->next = tmp;
     }
     return tmp;
}
/*
 * queue_pop(queue) pop the next element (FIFO order)
 * returns NULL if the queue is empty
 */
void* queue_pop(struct queue *queue);
/*
   if (queue_is_empty(queue))
   {
       return NULL;
   }
   if (queue-> store -> next == queue -> store ) 
   {
   	queue_init(queue);
   }
   struct list *a = queue -> store -> next -> next;
   queue -> store -> next -> next = NULL; 
   free (a);
   return queue;
}*/
