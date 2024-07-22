#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

struct s_node {
    set_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_set {
    unsigned int size;
    node_t first;
};

static bool
invrep(set s) {
    bool res = true;
    node_t move=NULL;

    if (s->size != 0u)
    {
        move = s->first;
        while (move->next != NULL && res)
        {
            res = move->elem < move->next->elem;
            move = move->next;
        }   
    }
    
    return res;
}

static struct s_node *
create_node(set_elem e) {
    node_t new_node=malloc(sizeof(struct s_node));

    new_node->elem = e;
    new_node->next = NULL;

    return new_node;
}


static struct s_node *
destroy_node(struct s_node *node) {
    free(node);
    node = NULL;

    return node;
}

/* CONSTRUCTORS */

set set_empty(void) {
    set s=malloc(sizeof(struct s_set));

    s->first = NULL;
    s->size = 0u;
    
    assert(invrep(s) && set_is_empty(s));
    return s;
}

set set_add(set s, set_elem e) {
    assert(invrep(s));
    node_t node = create_node(e);
    node_t move=NULL;
    node_t aux=NULL;

    if (set_is_empty(s))
    {
        s->first = node;
        s->size = s->size + 1;
    }
    else if (s->first->elem > e)
    {
        aux = s->first;
        s->first = node;
        node->next = aux;
        s->size = s->size + 1;
    }
    else
    {
        aux = s->first;
        move = aux->next;
        while (move != NULL && move->elem < e)
        {
            aux = aux->next;
            move = move->next;
        }
        if (move == NULL || (aux->elem != e && move->elem !=e))
        {
            aux->next = node;
            node->next = move;
            s->size = s->size + 1;
        }
        /*else if (move->elem != e)
        {
            aux->next = node;
            node->next = move;
            s->size = s->size + 1;
        }*/
        else
        {
            node = destroy_node(node);
        }
         
    }
    
    assert(invrep(s) && !set_is_empty(s));
    return s;
}

/* OPERATIONS   */
unsigned int set_cardinal(set s) {
    assert(invrep(s));

    unsigned int length=s->size;

    assert((length == 0) == set_is_empty(s));
    return length;
}

bool set_is_empty(set s) {
    assert(invrep(s));

    return s->size == 0u;
}

bool set_member(set_elem e, set s) {
    assert(invrep(s));
    node_t node=s->first;
    while (node!=NULL && node->elem < e) {
        node = node->next;
    }
    return node!=NULL && node->elem==e;
}

set set_elim(set s, set_elem e) {
    assert(invrep(s));
    node_t move=NULL;
    node_t aux=NULL;

    if (s->first->elem == e)
    {
        aux = s->first;
        s->first = s->first->next;
        aux = destroy_node(aux);
        s->size = s->size - 1;
    }
    else
    {
        aux = s->first;
        move = aux->next;
        while (move != NULL && move->elem < e)
        {
            aux = aux->next;
            move = move->next;
        }
        if (move != NULL && move->elem == e)
        {
            aux->next = move->next;
            move = destroy_node(move);
            s->size = s->size - 1;
        }
    }

    assert(invrep(s) && set_member(e, s));
    return s;
}

set_elem set_get(set s) {
    assert(invrep(s) && !set_is_empty(s));
    return s->first->elem;
}

set_elem* set_to_array(set s) {
    assert(invrep(s));
    set_elem* array=NULL;
    node_t move=NULL;

    if (!set_is_empty(s))
    {
        array = calloc(sizeof(set_elem), set_cardinal(s));
        move = s->first;
        for (unsigned int i = 0u; i < set_cardinal(s); ++i)
        {
            array[i] = move->elem;
            move = move->next;
        }
    }
    
    assert(!set_is_empty(s) == (array != NULL));
    return array;
}

set set_destroy(set s) {
    assert(invrep(s));
    node_t eraser=NULL;

    while (s->first != NULL)
    {
        eraser = s->first;
        s->first = s->first->next;
        eraser = destroy_node(eraser);
    }
    free(s);
    s = NULL;

    assert(s == NULL);
    return s;
}
