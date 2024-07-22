#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if (x >= 0)
    {
        y = x;
    }
    else
    {
        y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    
    a = -10;
    absolute(a, res);
    printf("%d \n", res);

    return EXIT_SUCCESS;
}

/*
El valor devuelto por pantalla es 0. Lo cual no coincide con el programa traducido en el pseudocódigo del teórico/práctico.
Esto se debe a la asginación de res en el main.
*/