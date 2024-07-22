#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* list as a pointer to structs to guarantee encapsulation */
typedef struct _list * list;
typedef int list_elem;


/* Constructors */
list empty_list(void);
/*
    Creates an empty list.
    Being l the returned list, list_is_empty(l) should be true.
*/

list addl_list(list_elem e, list l);
/*
    Returns the list l with the element e added at the beginning.
*/


/* Operations */
bool is_empty_list(list l);
/*
    Returns True if l is empty.
*/

list_elem head_list(list l);
/*
    Returns the first element of the list l.
    PRECONDITION: !list_is_empty(l)
*/

list tail_list(list l);
/*
    Returns the list l with the first element deleted.
    PRECONDITION: !list_is_empty(l)
*/

list addr_list(list l, list_elem e);
/*
    Returns the list l with the element e added at the end.
*/

unsigned int length_list(list l);
/*
    Returns the amount of elements in the list l.
*/

list concat_list(list l, list l0);
/*
    Returns the list with all elements of l and l0 in that order.
*/

list_elem index_list(list l, unsigned int n);
/*
    Returns the n-th element of the list l.
    PRECONDITION: length(l) > n
*/

list take_list(list l, unsigned int n);
/*
    Leaves the first n elements in the list l.
*/

list drop_list(list l, unsigned int n);
/*
    Eliminates the first n elements of the list l.
*/

list copy_list(list l);
/*
    Makes a copy of list l.
*/


/* Destroy */
list destroy_list(list l);
/*
    Frees memory if necessary.
*/


#endif