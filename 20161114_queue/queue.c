#include <stddef.h>
#include <stdlib.h>
#include "queue.h"

/*
 * queue_init(queue) initialize an empty queue container
 * allocation of the container is kept external for more flexibility
 */
void queue_init(struct queue *queue)
{
    queue->store=NULL;
    queue->size=0;
}

/*
 * queue_is_empty(queue) test for emptyness
 */
int queue_is_empty(struct queue *queue)
{
    return(queue->store ==NULL);
}

/*
 * queue_push(queue, elm) push elm
 */
void queue_push(struct queue *queue, void *elm)
{
    struct list *e = malloc(sizeof(elm));
    if(queue_is_empty(queue))
    {
        queue_init(queue);
        queue->store = malloc(sizeof(elm));
        queue->store->next = e;
        queue->store->next->next=queue->store;

        queue->size = 1;
    }
    else
    {
        struct queue *q = malloc(sizeof(struct queue));
        q->store->next=e;
        q->store->next->next = queue->store;
        q->size=queue->size +1;
    }


}
void* queue_pop(struct queue *queue)
{
    if (queue_is_empty(queue))
    {
        return NULL;
    }
    if (queue->store->next == queue->store)
    {
        queue_init((queue));
    }
    struct list *A = queue->store->next;
    queue->store->next = queue->store->next->next;
    free(A);
    return queue;

}
