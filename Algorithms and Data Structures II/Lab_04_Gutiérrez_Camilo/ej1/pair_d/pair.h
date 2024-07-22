#ifndef _PAIR_H
#define _PAIR_H

typedef struct s_pair_t * pair_t;
typedef int elem;

pair_t pair_new(elem x, elem y);
/*
 * DESC: Creates a new pair with components (x, y)
 *
 * p = pair_new(x, y);
 *
 * POS: {p --> (x, y)}
 */

elem pair_first(pair_t p);
/*
 * DESC: Returns the first component of p
 *
 * PRE: {p --> (x, y)}
 *
 *  fst = pair_first(p);
 *
 * POS: {fst == x}
 */

elem pair_second(pair_t p);
/*
 * DESC: Returns the second component of p
 *
 * PRE: {p --> (x, y)}
 *
 *  snd = pair_second(p);
 *
 * POS: {snd == y}
 */

pair_t pair_swapped(pair_t p);
/*
 * DESC: Return a NEW pair with the components of p reversed
 *
 * PRE: {p --> (x, y)}
 *
 *  q = pair_swapped(p)
 *
 * POS: {pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p)}
 *
 */

pair_t pair_destroy(pair_t p);
/*
 * DESC: Free memory if its necesary
 *
 */


#endif

/*
    Contestando a la pregunta: "¿Qué diferencia hay entre la especificación anterior y la que se encuentra en el pair.h de la carpeta pair_d?"
    Básicamente la única diferencia es que en esta especificación, en vez de usar el tipo nativo 'int', se utiliza el nuevo tipo 'elem' el cual es un sinónimo de int.
*/