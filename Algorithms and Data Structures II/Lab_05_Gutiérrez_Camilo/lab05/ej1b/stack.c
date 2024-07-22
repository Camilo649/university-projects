#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "stack.h"
 
typedef struct _s_stack_node *stack_node;

struct _s_stack_node{
    stack_elem e;
    stack_node next;
};

typedef unsigned int size;

struct _s_stack{
    stack_node elem;
    size length;
};

static bool invrep(stack s){
    stack_node move=NULL;
    unsigned int count;

    move = s->elem;
    count = 0u;
    while (move != NULL) {
        move = move->next;
        ++count;
    }
        
        return (s != NULL && s->length == count);
    }

stack stack_empty(){
    stack s=NULL;

    s = malloc(sizeof(struct _s_stack));
    s->elem = NULL;
    s->length = 0u;

    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    return s;
}

stack stack_push(stack s, stack_elem e){
    stack_node container=NULL;
    
    container = malloc(sizeof(struct _s_stack_node));

    container->e = e;
    container->next = s->elem;
    s->elem = container;
    s->length = s->length + 1u;

    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    assert(!stack_is_empty(s)); //PRE
    stack_node eraser=NULL;

    eraser = s->elem;
    s->elem = s->elem->next;
    s->length = s->length -1;
    free(eraser);

    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    return s;
}

unsigned int stack_size(stack s){
    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    
    return s->length;
}

stack_elem stack_top(stack s){
    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    assert(!stack_is_empty(s)); //PRE

    return s->elem->e;
}

bool stack_is_empty(stack s){
    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    
    return s->elem == NULL && s->length == 0u;
}

stack_elem *stack_to_array(stack s){
    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    stack_elem *array=NULL;
    stack_node move=NULL;

    if (!stack_is_empty(s)) //Esta guarda es necesaria porque calloc(sizeof(type), 0) puede devolver NULL;
    {
        array = calloc(sizeof(stack_elem), s->length);
        move = s->elem;
        for (unsigned int l=s->length; l > 0u; --l)
        {
            array[l-1] = move->e; //Indexo desde 0;
            move = move->next;
        }
    }
    
    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    return array;
}

stack stack_copy(stack s){
    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    stack s_copy=stack_empty();
    stack_node move=NULL;

        move = s->elem;
        for (unsigned int i=0u; i < s->length; ++i)
        {
            s_copy = stack_push(s_copy, move->e);
            move = move->next;
        }
        s_copy->length = s->length;
    
    assert(invrep(s) && invrep(s_copy)); //INVARIANTE DE REPRESENTACIÓN
    return s_copy;
}

stack stack_destroy(stack s){
    assert(invrep(s)); //INVARIANTE DE REPRESENTACIÓN
    stack_node eraser=NULL;

    while (s->elem != NULL)
    {
        eraser = s->elem;
        s->elem = s->elem->next;
        free(eraser);
    }
    free(s);
    s = NULL;
    
    return s;
}