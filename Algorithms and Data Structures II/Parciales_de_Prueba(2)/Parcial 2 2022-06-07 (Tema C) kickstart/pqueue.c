#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node **priorities;
    priority_t min_priority;
    priority_t max_priority;
    size_t size;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node=NULL;
    
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;

    return node;
}


static bool invrep(pqueue q) {

    return q != NULL;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q=NULL;
    
    q = malloc(sizeof(struct s_pqueue));
    assert(q!=NULL);
    q->size = 0;
    q->min_priority = min_priority;
    q->max_priority = INT_MAX;
    q->priorities = malloc(sizeof(struct s_node) * (min_priority + 1));
    assert(q->priorities!=NULL);
    for (priority_t p = 0u; p <= min_priority; ++p)
    {
        q->priorities[p] = NULL;
    }

    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    struct s_node* new_node=NULL;
    struct s_node* move=NULL;

    if (priority <= q->min_priority)
    {
        new_node = create_node(e);
        if (q->priorities[priority] == NULL)
        {
            q->priorities[priority] = new_node;
        }
        else
        {
            move = q->priorities[priority];
            while (move->next != NULL)
            {
                move = move->next;
            }
            move->next = new_node;
        }
        q->size = q->size + 1;
        if (priority < q->max_priority)
        {
            q->max_priority = priority;
        }
        

        assert(invrep(q) && !pqueue_is_empty(q));
    }

    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));

    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t p=0u;

    while (q->priorities[p] == NULL)
    {
        ++p;
    }

    return q->priorities[p]->elem;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));

    return q->max_priority;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));

    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t p=0u;
    struct s_node *eraser=NULL;

    eraser = q->priorities[q->max_priority];
    q->priorities[q->max_priority] = q->priorities[q->max_priority]->next;
    free(eraser);
    eraser = NULL;
    q->size = q->size - 1;
    if (pqueue_is_empty(q))
    {
        q->max_priority = INT_MAX;
    }
    else if (q->priorities[q->max_priority] == NULL)
    {
        p = q->max_priority;
        while (q->priorities[p] == NULL)
        {
            ++p;
        }
        q->max_priority = p;
    }

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *move=NULL;
    struct s_node *eraser=NULL;
    
    for (priority_t p = 0u; p <= q->min_priority; ++p)
    {
        if (q->priorities[p] != NULL)
        {
            move = q->priorities[p];
            while (move != NULL)
            {
                eraser = move;
                move = move->next;
                eraser = destroy_node(eraser);
                eraser = NULL;
            }
        }
    }
    free(q->priorities);
    q->priorities = NULL;
    free(q);
    q = NULL;

    return q;
}
