/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include "helpers.h"
#include "sort.h"
#include "song.h"

/*Para la siguiente comparación, considero que si dos canciones tienen el mismo año
de copyright, da lo mismo cual va primero y por lo tanto las considero ordenadas.*/
bool goes_before(song_t s1, song_t s2) {
    return s1.year <= s2.year;
}

bool array_is_sorted(song_t playlist[], unsigned int length) {
    unsigned int i = 0u;
    bool sorted = true;
    while (i + 1 < length && sorted) {
        sorted = goes_before(playlist[i], playlist[i + 1]);
        i = i + 1;
    }
    return sorted;
}
