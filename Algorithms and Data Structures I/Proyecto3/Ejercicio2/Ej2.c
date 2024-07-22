#include <stdio.h>
#include <stdbool.h>

int main (void)

{
    printf ("Ejercicio 2\n");
    
    int x;
    int y;
    int z;
    int b;
    int w;
    
    printf ("Ingrese un valor para x\n");
    scanf ("%d", &x);
    printf ("Ingrese un valor para y\n");
    scanf ("%d", &y);
    printf ("Ingrese un valor para z\n");
    scanf ("%d", &z);
    printf ("Ingrese un valor para b\n");
    scanf ("%d", &b);
    printf ("Ingrese un valor para w\n");
    scanf ("%d", &w);

    int r;
    r = expresion1 (x);
    r = expresion2 (x, y, z);
    r = expresion3 (b, w);

    return 0;
}

int expresion1 (int x)
{
    if(x % 4 == 0) printf ("True\n");
    else printf ("False\n");
}

int expresion2 (int x, int y, int z)
{
    if(x + y == 0 && y - x == (-1) * z) printf ("True\n");
    else printf ("False\n");
}

int expresion3 (int b, int w)
{
    if((- b) && w) printf ("True\n");
    else printf ("False\n");
}

/* 
Un estado que satisface la consigna es:
x -> 4, y -> -4, z -> 8, b -> 1(True), w -> 0(False).
de tal forma que queda:
Expresion                       |Valor
x % 4 == 0                      |True
x + y == 0 && y - x == (-1) * z |True
not b && w                      |False 
*/