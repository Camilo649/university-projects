/* First, the standard lib includes, alphabetically ordered */
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "stack.h"

static const stack_elem TEST_ELEM = 6;
static const unsigned int LENGTH = 5;

void stack_dump(stack s){
    stack s_copy=stack_copy(s);

    while (!stack_is_empty(s_copy))
    {
        printf("%d\n", stack_top(s_copy));
        s_copy = stack_pop(s_copy);
    }
    printf("...\n");
    stack_destroy(s_copy);
}

void array_dump(int a[], unsigned int length) {
    for (unsigned int i = 0u; i < length; ++i) {
        fprintf(stdout, "%i", a[i]);
        if (i < length - 1) {
            fprintf(stdout, " ");
        } else {
            fprintf(stdout, "\n");
        }
    }
}

int main(void) {

    /* create a empty stack and an array */
    stack stack=stack_empty();
    stack_elem *array;

    /* add any element, in this case 6 */
    stack = stack_push(stack, TEST_ELEM);

    /* show the stack in the screen */
    printf("Initial:\n");
    stack_dump(stack);

    /* removes the element with stack_pop() */
    stack = stack_pop(stack);

    /* show the new stack in the screen */
    printf("After stack_pop():\n");
    stack_dump(stack);

    /* add the element again */
    stack = stack_push(stack, TEST_ELEM);

    /* show the original stack in the screen */
    printf("After stack_push():\n");
    stack_dump(stack);

    /* restarts the stack for testing */
    stack_destroy(stack);
    stack = stack_empty();

    /* pass the stack to the array */
    array = stack_to_array(stack);

    if (array == NULL)
    {
        printf("stack_to_array() funciona para pilas vacías.\n");
    }
    else
    {
         printf("stack_to_array() NO funciona para pilas vacías.\n");
    }
    
    /* adds TEST_STACK_LENGTH elements to the stack */
    for (unsigned int i = 1; i <= LENGTH; ++i)
    {
        stack = stack_push(stack, i);
    }
    
    /* pass the new stack to the array */
    array = stack_to_array(stack);

    /* show the array in the screen */
    array_dump(array, LENGTH);

    stack = stack_destroy(stack);
    free(array);

    return (EXIT_SUCCESS);
}