#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

struct _s_queue {
    queue_elem elem;
    struct _s_queue *next;
};

queue queue_empty(void) {
    return NULL;
}

queue queue_enqueue(queue q, queue_elem e) {
    queue new_node = calloc(1, sizeof(struct _s_queue));
    new_node->elem= e;
    new_node->next = q;
    q = new_node;
    return q;
}

bool queue_is_empty(queue q) {
    return q == NULL;
}

queue_elem queue_first(queue q) {
    assert(!queue_is_empty(q));
    queue move;

    move = q;
    while (move->next != NULL)
    {
        move = move->next;
    }
    
    return move->elem;
}

unsigned int queue_size(queue q) {
    unsigned int size=0;
    while (q != NULL) {
        size++;
        q = q->next;
    }
    return size;
}

queue queue_dequeue(queue q) {
    assert(!queue_is_empty(q));
    queue move;
    queue eraser;

    if (queue_size(q) == 1)
    {
        free(q);
        q = NULL;
    }
    else
    {
        move = q;
        while (move->next->next != NULL)
        {
            move = move->next;
        }
        eraser = move->next;
        free(eraser);
        move->next = NULL;
    }

    return q;
}

queue queue_destroy(queue q) {
    queue aux=NULL;
    while (q != NULL) {
        aux=q;
        q = q->next;
        free(aux);
    }
    return q;
}
