/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include <assert.h>
#include "helpers.h"
#include "sort.h"
#include "movie.h"

bool goes_before(movie_t s1, movie_t s2)
{

    return s1.runtime <= s2.runtime;
}

unsigned int array_sorted_until(movie_t movielist[], unsigned int size)
{
    unsigned int ord_pos=0u;

    while (ord_pos < (size - 1) && goes_before(movielist[ord_pos], movielist[ord_pos + 1]))
    {
        ++ord_pos;
    }

    return ord_pos;
}
