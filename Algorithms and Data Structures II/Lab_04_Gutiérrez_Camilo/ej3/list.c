#include <stdbool.h>
#include <stdlib.h>
#include "assert.h"

#include "list.h"

struct _list{
    list_elem elem;
    list next;
};

list empty_list(void){
    list l=NULL;

    return l;
}

list addl_list(list_elem e, list l){
    list container=NULL;
    
    container = malloc(sizeof(struct _list));
    container->elem = e;
    container->next = l;
    l = container;

    return l;
}


bool is_empty_list(list l){
    
    return l == NULL;
}

list_elem head_list(list l){
    assert(!is_empty_list(l)); //PRE

    return l->elem;
}

list tail_list(list l){
    assert(!is_empty_list(l)); //PRE
    list borrador=NULL;

    borrador = l;
    l = l->next;
    free(borrador);

    return l;
}

list addr_list(list l, list_elem e){
    list container=NULL;
    list move=NULL;
    
    container = malloc(sizeof(struct _list));
    container->elem = e;
    container->next = NULL;
    if (is_empty_list(l))
    {
        l = container;
    }
    else
    {
        move = l;
        while (move->next != NULL)
        {
            move = move->next;
        }
        move->next = container;
    }
    
    return l;
}

unsigned int length_list(list l){
    list move=NULL;
    unsigned int n = 0u;

    move = l;
    while (!is_empty_list(move))
    {
        ++n;
        move = move->next;
    }
    
    return n;
}

list concat_list(list l, list l0){
    list move=NULL;

    if (is_empty_list(l))
    {   
        l = l0;
    }
    else if (!is_empty_list(l0))
    {
        move = l;
        while (move->next != NULL)
        {
            move = move->next;
        }
        move->next = l0;
    }
    
    return l;
}

list_elem index_list(list l, unsigned int n){
    assert(length_list(l) > n); //PRE
    list_elem e;
    list move=NULL;

    move = l;
    for (unsigned int i = 0u; i < n; ++i) //Notar que no necesito hacer un caso para una lista vacía pues length([]) devuelve 0 y debido a mi precondición, estaría forzando llamar a index con un unsigned int < 0 lo cual no existe.
    {
        move = move->next;
    }
    e = move->elem;

    return e;
}

list take_list(list l, unsigned int n){
    list move=NULL;
    list borrador=NULL;
    unsigned int i;

    move = l;
    i = 0u;
    while (i < n && move != NULL)
    {
        move = move->next;
        i++;
    }
    while (move != NULL)
    {
        borrador = move;
        move = move->next;
        free(borrador);
    }
    
    return l;
}

list drop_list(list l, unsigned int n){
    list borrador=NULL;
    unsigned int i;

    i = 0u;
    while (i < n && l != NULL)
    {
        borrador = l;
        l = l->next;
        free(borrador);
        i++;
    }
    
    return l;
}

list copy_list(list l){
    list l_copy;

    if (is_empty_list(l))
    {
        l_copy = NULL;
    }
    else
    {
        l_copy = malloc(sizeof(struct _list));
        l_copy->elem = l->elem;
        l_copy->next = copy_list(l->next); 
    }

    return l_copy;
}


list destroy_list(list l){
    list borrador=NULL;

    while (l != NULL)
    {
        borrador = l;
        l = l->next;
        free(borrador);
    }
    
    return l;
}