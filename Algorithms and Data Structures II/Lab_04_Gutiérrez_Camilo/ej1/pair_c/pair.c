#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "assert.h"  /* assert()...     */
#include "pair.h"    /* TAD Par         */

struct s_pair_t {
    int fst;
    int snd;
};

pair_t pair_new(int x, int y) {
    pair_t p=NULL;
    p = malloc(sizeof(pair_t));

    p->fst = x;
    p->snd = y;

    assert(p->fst == x && p->snd == y); //POS
    return p;
}

//No le pongo PRE ni POS porque la expresión a comparar es trivial
int pair_first(pair_t p) {
    if (p == NULL)
    {
        printf("El par no fue incializado \n");
        exit(EXIT_FAILURE);
    }
   
    return p->fst;
}

//No le pongo PRE ni POS porque la expresión a comparar es trivial
int pair_second(pair_t p) {
    if (p == NULL)
    {
        printf("El par no fue incializado \n");
        exit(EXIT_FAILURE);
    }

    return p->snd;
}

pair_t pair_swapped(pair_t p) {
    if (p == NULL)
    {
        printf("El par no fue incializado \n");
        exit(EXIT_FAILURE);
    }
    assert(p->fst == pair_first(p) && p->snd == pair_second(p)); //PRE
    
    pair_t q = pair_new(p->snd, p->fst);

    assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)); //POS
    return q; //También simplemente podría haber devuelto: return pair_new(p->snd, p->fst); y fijarme que el puntero que me pasan como parámetro sea distinto de NULL.
}

pair_t copy_pair(pair_t p1) {
    if (p1 == NULL)
    {
        printf("El par no fue incializado \n");
        exit(EXIT_FAILURE);
    }
    assert(p1->fst == pair_first(p1) && p1->snd == pair_second(p1)); //PRE
    
    pair_t p2 = pair_new(p1->fst, p1->snd);

    assert(p2->fst == pair_first(p1) && p2->snd == pair_second(p1)); //POS
    return p2; //También simplemente podría haber devuelto: return pair_new(p1->fst, p1->snd); y fijarme que el puntero que me pasan como parámetro sea distinto de NULL.
}

pair_t pair_destroy(pair_t p) {
    if (p != NULL)
    {
        free(p);
    }

    return p;
}