#include <stdbool.h>

#include "pivot.h"

bool is_pivot(int array[], unsigned int length, unsigned int piv) {
    bool res=true;
    unsigned int i=0u;
    unsigned int j=length;

    while (i<piv && res)
    {
        res = (array[i] <= array[piv]);
        ++i;
    }
    while (j>piv && res)
    {
        res = (array[j] > array[piv]);
        --j;
    }

    return res;
}
