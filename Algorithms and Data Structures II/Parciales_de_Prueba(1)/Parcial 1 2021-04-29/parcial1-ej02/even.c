#include <stdbool.h>
#include "even.h"

bool is_even_sorted(int array[], unsigned int length) {
    bool even_sorted=true;
    unsigned int even_pos=2u;

    while (even_pos<length && even_sorted)
    {
        even_sorted = array[even_pos - 2] <= array[even_pos];
        even_pos += 2;
    }
    
    return even_sorted;
}

