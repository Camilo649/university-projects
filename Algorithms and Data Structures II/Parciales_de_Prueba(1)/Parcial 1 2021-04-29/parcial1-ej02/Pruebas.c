#include <stdio.h>

#include "even.h"

int main()
{
    int a[5] = {1, 6, 2, 0, -1};

    is_even_sorted(a, 5) ? printf("Las posiciones pares del arreglo estan ordenadas de manera ascendente.\n") :
                           printf("Las posiciones del arreglo NO están ordenadas.\n");

    return 0;
}
