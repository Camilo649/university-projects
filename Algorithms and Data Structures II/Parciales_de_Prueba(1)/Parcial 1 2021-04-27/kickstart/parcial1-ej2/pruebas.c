#include <stdio.h>

#include "odd.h"

int main()
{
    int a[6] = {5, 1, 8, 2, 3,-1};

    is_odd_sorted(a, 6) ? printf("Las posciones impares del arreglo están ordenadas ascendentemente.\n") : 
                          printf("Las posciones impares del arreglo NO están ordenadas ascendentemente.\n");

    return 0;
}
