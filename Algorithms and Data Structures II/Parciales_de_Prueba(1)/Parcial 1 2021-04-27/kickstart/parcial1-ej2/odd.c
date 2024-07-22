#include <stdbool.h>

#include "odd.h"

bool is_odd_sorted(int array[], unsigned int length) {
    bool odd_sorted=true;
    unsigned int i=3u;

    while (i<length && odd_sorted)
    {
        odd_sorted = array[i - 2] <= array [i];
        i += 2;
    }

    return odd_sorted;
}
