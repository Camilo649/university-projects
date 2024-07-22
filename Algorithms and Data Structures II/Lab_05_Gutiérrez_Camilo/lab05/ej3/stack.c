#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#define INITIAL_CAPACITY 10

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

static bool invrep(stack s){
    bool result=(s != NULL) && (s->size <= s->capacity);
    bool arithmetic=true; //Chequea que se puedan hacer operaciones aritméticas con los elementos del array.
    unsigned int i=0u;

    if (result)
    {
        while (i < s->size && arithmetic)
        {
            arithmetic = ((s->elems[i] - s->elems[i]) == 0);
            ++i;
        }
    }
    
    return result && arithmetic;
    /*
    Verifico que mi stack no sea NULL. 
    Chequeo que la capacidad y la longitud del arreglo tengan sentido. 
    También reviso que se pueda acceder a cada elemento del array, que no se modifque si accedo a él más de una vez y que pueda realizar operaciones aritméticas con cada uno de ellos.
    */
}

stack stack_empty(){
    stack s=NULL;
    
    s = malloc(sizeof(struct _s_stack));
    s->elems = calloc(sizeof(stack_elem), INITIAL_CAPACITY);
    s->size = 0u;
    s->capacity = INITIAL_CAPACITY;
    
    assert(invrep(s)); //Invariante de Representación
    return s;
}

stack stack_push(stack s, stack_elem e) {
    
    if (s->size == s->capacity) 
    {
        s->capacity = (s->capacity * 2);
        s->elems = realloc(s->elems, sizeof(stack_elem) * s->capacity);
    }
    s->elems[s->size] = e;
    s->size = s->size + 1u;

    assert(invrep(s)); //Invariante de Representación
    return s;
}

stack stack_pop(stack s){
    assert(invrep(s)); //Invariante de Representación
    assert(!stack_is_empty(s)); //PRE

    s->size = s->size -1u;
    
    assert(invrep(s)); //Invariante de Representación
    return s;
}

unsigned int stack_size(stack s){
    assert(invrep(s)); //Invariante de Representación

    return s->size;
}

stack_elem stack_top(stack s){
    assert(invrep(s)); //Invariante de Representación

    return s->elems[s->size-1u];
}

bool stack_is_empty(stack s){
    assert(invrep(s)); //Invariante de Representación

    return (s->size == 0u);
}

stack_elem *stack_to_array(stack s){
    assert(invrep(s)); //Invariante de Representación
    stack_elem *array=NULL;
    
    if (!stack_is_empty(s)) //Esta guarda es necesaria porque calloc(sizeof(type), 0) puede devolver NULL;
    {
        array = calloc(sizeof(stack_elem), s->size);
        for (unsigned int i=0u; i < s->size; ++i)
        {
            array[i] = s->elems[i];
        }
    }
    
    assert(invrep(s)); //Invariante de Representación
    return array;
}

stack stack_copy(stack s){
    assert(invrep(s)); //Invariante de Representación
    stack s_copy=stack_empty();

    if (!stack_is_empty(s)){
    
        s_copy->size = s->size;
        s_copy->capacity = s->size;
        for (unsigned int i=0u; i < s->size; ++i)
        {
            s_copy->elems[i] = s->elems[i];
        }
    }

    assert(invrep(s) && invrep(s_copy)); //Invariante de Representación
    return s_copy;
}

stack stack_destroy(stack s){
    assert(invrep(s)); //Invariante de Representación

    free(s->elems);
    s->elems = NULL;
    free(s);
    s = NULL;

    return s;
}