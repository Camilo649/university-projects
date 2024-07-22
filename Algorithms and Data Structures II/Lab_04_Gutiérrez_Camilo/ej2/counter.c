#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "assert.h"

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter c=NULL;
    c = malloc(sizeof(struct _counter));

    c->count = 0u;

    assert(counter_is_init(c)); //PRE
    return c;
}

void counter_inc(counter c) {
    if (c == NULL)
    {
        printf("El contador no fue incializado \n");
        exit(EXIT_FAILURE);
    }
    
    c->count = c->count + 1u;
}

bool counter_is_init(counter c) {
    if (c == NULL)
    {
        printf("El contador no fue incializado \n");
        exit(EXIT_FAILURE);
    }

    return c->count == 0u;
}

void counter_dec(counter c) {
    if (c == NULL)
    {
        printf("El contador no fue incializado \n");
        exit(EXIT_FAILURE);
    }
    assert(!counter_is_init(c)); //PRE
    
    c->count = c->count - 1;
}

counter counter_copy(counter c) {
    if (c == NULL)
    {
        printf("El contador no fue incializado \n");
        exit(EXIT_FAILURE);
    }
    counter c2=NULL;
    c2 = malloc(sizeof(struct _counter));

    c2->count = c->count;

    return c2;
}

void counter_destroy(counter c) {
    if (c != NULL)
    {
        free(c);
    }
}