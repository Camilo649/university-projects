/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include <assert.h>
#include "helpers.h"
#include "sort.h"
#include "movie.h"

static float calculate_preference(movie_t movie){
    
    return movie.n_votes * movie.avg_rating;
}

/*Asumo que si dos películas tienen la misma preferencia
es decir, el mismo producto de entre la cantidad de votos
y su promedio de rating, tambíen se las considera ordenadas.*/
bool goes_before(movie_t s1, movie_t s2) {
    
    return calculate_preference(s1) >= calculate_preference(s2);
}

bool array_is_sorted(movie_t movielist[], unsigned int size) {
    bool sorted=true;
    unsigned int i=0u;
    while (sorted && i + 1 < size) {
        sorted = goes_before(movielist[i], movielist[i+1]);
        ++i;
    }
    return sorted;
}
