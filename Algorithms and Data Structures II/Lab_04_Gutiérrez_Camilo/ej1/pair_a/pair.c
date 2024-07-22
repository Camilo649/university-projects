#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "assert.h"  /* assert()...     */
#include "pair.h"    /* TAD Par         */

pair_t pair_new(int x, int y) {
    pair_t p;

    p.fst = x;
    p.snd = y;

    assert(p.fst == x && p.snd == y); //POS
    return p;
}

//No le pongo PRE ni POS porque la expresión a comparar es trivial
int pair_first(pair_t p) {
   
    return p.fst;
}

//No le pongo PRE ni POS porque la expresión a comparar es trivial
int pair_second(pair_t p) {

    return p.snd;
}

pair_t pair_swapped(pair_t p) {
    assert(p.fst == pair_first(p) && p.snd == pair_second(p)); //PRE
    pair_t q;

    q.fst = p.snd;
    q.snd = p.fst;

    assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)); //POS
    return q;
}

pair_t copy_pair(pair_t p1) {
    assert(p1.fst == pair_first(p1) && p1.snd == pair_second(p1)); //PRE
    pair_t p2;

    p2 = p1;

    assert(p2.fst == pair_first(p1) && p2.snd == pair_second(p1)); //POS
    return p2; //También podría aprovecharme del pasaje por copia de C y simplemente hacer: return p1;
}

pair_t pair_destroy(pair_t p) {

    return p; //Como nunca alojé nada en memoria dinámica (heap) no necesito hacer free() de nada.
}