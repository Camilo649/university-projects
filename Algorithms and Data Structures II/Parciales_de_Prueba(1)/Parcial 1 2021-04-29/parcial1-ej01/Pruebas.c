#include <stdio.h>

#include "sorted.h"

int main()
{
    int a[5] = {1, 3, 4, 5, 5};

    printf("El arreglo está ordenado hasta la posición %d. \n", sorted_until(a, 5));

    return 0;
}
