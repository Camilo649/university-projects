/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    
    return ((*x).rank <= (*y).rank);
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

/*Voy a ordenar implementando la idea del quick_sort*/

static void swap(player_t a[], unsigned int i, unsigned int j)
{
    player_t player_aux = a[i];
    a[i] = a[j];
    a[j] = player_aux;
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv, i, j;
    ppiv = izq;
    i = izq + 1;
    j = der;

    while (i <= j)
    {
        if (goes_before(a[i], a[ppiv]))
        {
            ++i;
        }
        else if (goes_before(a[ppiv], a[j]))
        {
            --j;
        }
        else if (goes_before(a[ppiv], a[i]) && goes_before(a[j], a[ppiv]))
        {
            swap(a, i, j);
            ++i;
            --j;
        } 
    }
    swap(a, ppiv, j);
    ppiv = j;

    return ppiv;
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;

    if (der > izq)
    {
        ppiv = partition(a, izq, der);
        quick_sort_rec(a, izq, ((ppiv == 0u) ? 0u : ppiv -1u));
        quick_sort_rec(a, ppiv + 1u, der);
    }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u);
}