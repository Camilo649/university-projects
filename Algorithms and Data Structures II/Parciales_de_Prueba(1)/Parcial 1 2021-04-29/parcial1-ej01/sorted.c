#include "sorted.h"

unsigned int sorted_until(int array[], unsigned int size) {
    unsigned int ord_pos=0u;

    while (ord_pos < (size - 1) && array[ord_pos] <= array[ord_pos + 1])
    {
        ++ord_pos;
    }

    return ord_pos;
}
