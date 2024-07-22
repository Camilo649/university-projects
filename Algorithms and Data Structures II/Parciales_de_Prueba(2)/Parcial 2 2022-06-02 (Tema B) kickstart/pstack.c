#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *front;
    priority_t max_priority;
    size_t size;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next; 
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
   
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    
    free(node);
    node = NULL;

    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    bool inv = s ==  NULL? false : true;
    size_t length = 0;
    struct s_node * move = NULL;

    if (inv && !pstack_is_empty(s))
    {
        inv = (s->front->priority == s->max_priority); //Front debe apuntar al elemento de mayor prioridad 
        move = s->front;
        length = s->size;
        for (size_t i = 1; i < length; ++i)
        {
            inv = (move->priority >= move->next->priority);
        }
    }

    return inv;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    
    s = malloc(sizeof(struct s_pstack));
    assert(s != NULL);
    s->front = NULL;
    s->size = 0;

    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    struct s_node * move = NULL;
    struct s_node * s_aux = NULL;
    
    if (pstack_is_empty(s))
    {
        s->front = new_node;
        s->max_priority = new_node->priority;
        s->max_priority = priority; //Actualizo la máxima prioridad actual
    }
    else if (priority >= s->max_priority)
    {
        new_node->next = s->front;
        s->front = new_node;
        s->max_priority = priority; //Actualizo la máxima prioridad actual
    }
    else
    {
        move = s->front;
        s_aux = move->next;
        while (move->next !=NULL && move->next->priority > priority)
        {
            move = move->next;
            s_aux = move->next;
        }
        move->next = new_node;
        new_node->next = s_aux;
    }
    s->size = s->size + 1;

    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {

    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    return s->front->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));

    return s->max_priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
   
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node * eraser = NULL;

    eraser = s->front;
    s->front = s->front->next;
    if (s->front != NULL)
    {
        s->max_priority = s->front->priority; //Actualizo la máxima prioridad si es que todavía tengo elementos.
    }
    eraser = destroy_node(eraser);
    s->size = s->size - 1;

    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node * move = NULL;
    struct s_node * eraser = NULL;

    if (!pstack_is_empty(s))
    {
        move = s->front;
        while (move != NULL)
        {
            eraser = move;
            move = move->next;
            eraser = destroy_node(eraser);
        }
    }
    free(s);
    s = NULL;

    assert(s == NULL);
    return s;
}
