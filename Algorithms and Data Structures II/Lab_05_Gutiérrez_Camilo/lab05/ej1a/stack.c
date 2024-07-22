#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "stack.h"
 
struct _s_stack{
    stack_elem elem;
    stack next;
};

stack stack_empty(){
    
    return NULL;
}

stack stack_push(stack s, stack_elem e){
    stack container=NULL;
    
    container = malloc(sizeof(struct _s_stack));
    container->elem = e;
    container->next = s;
    s = container;

    return s;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s)); //PRE
    stack eraser=NULL;

    eraser = s;
    s = s->next;
    free(eraser);

    return s;
}

unsigned int stack_size(stack s){
    unsigned int current_length=0u;
    stack move=NULL;

    move = s;
    while (move != NULL)
    {
        ++current_length;
        move = move->next;
    }
    
    return current_length;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s)); //PRE

    return s->elem;
}

bool stack_is_empty(stack s){

    return s==NULL;
}

stack_elem *stack_to_array(stack s){
    stack_elem *array=NULL;
    stack move=NULL;
    unsigned int length=0u;

    if (!stack_is_empty(s)) //Esta guarda es necesaria porque calloc(sizeof(type), 0) no devuelve NULL;
    {
        length=stack_size(s);
        move = s;
        array = calloc(sizeof(stack_elem), length);
        for (unsigned int l=length; l > 0u; --l) //No necesito corroborar si move es != NULL pues ya tengo la cantidad de elementos de la pila s.
        {
            array[l-1u] = stack_top(move); //Indexo desde 0;
            move = move->next;
        }
    }
    
    return array;
}

stack stack_copy(stack s){
    stack s_copy;

    if (stack_is_empty(s))
    {
        s_copy = NULL;
    }
    else
    {
        s_copy = malloc(sizeof(struct _s_stack));
        s_copy->elem = s->elem;
        s_copy->next = stack_copy(s->next);  
    }
    
    return s_copy;
}

stack stack_destroy(stack s){
    stack eraser=NULL;

    while (s != NULL)
    {
        eraser = s;
        s = s->next;
        free(eraser);
    }
    
    return s;
}