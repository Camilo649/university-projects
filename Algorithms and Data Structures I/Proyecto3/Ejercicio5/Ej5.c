#include <stdio.h>
#include <stdbool.h>

int h (int i) 
{
    printf("%d\n",i);    
    while (i != 0)
    {
        i = i - 1;
        printf("%d\n",i);
    }
    return 0;
}

int I (int i) 
{
    printf("%d\n",i);
    while (i != 0)
    {
        i = 0;
        printf("%d\n",i);
    }
    return 0;
}

int p1 (int x, int y, int i)
{
    i = 0;
    while (x >= y)
    {
        x = x - y;
        i = i + 1;
        printf("Los estados son: x -> %d, y -> %d, i -> %d\n", x,y,i);
    }
    return 0;
}

int p2 (int x, int i, bool res, int j)
{
    res = j;
    i = 2;
    res = true;
    while (i < x && res)
    {
        res = res && (x % i != 0);
        i = i + 1;
        printf ("x -> %d i -> %d res -> %d\n",x,i,res);
    }
    return 0;
} 

int main (void)

{
    printf ("Ejercicio 5a\n");
    
    int x;
    int y;
    int i;
    bool res;
    int j;
    int r;
  
    printf ("Ingrese un indice para el primer programa \n");
    scanf ("%d", &i);

    r = h (i);

    printf ("Ingrese un indice para el segundo programa \n");
    scanf ("%d", &i);

    r = I (i);

    printf ("Ejercicio 5b\n");

    printf("Ingrese un valor para 'x' \n");
    scanf("%d", &x);
    printf("Ingrese un valor para 'y' \n");
    scanf("%d", &y);
    printf("Ingrese un indice \n");
    scanf("%d", &i);

    r = p1 (x,y,i);

    printf ("Ingrese un valor para 'x' \n");
    scanf ("%d", &x);
    printf ("Ingrese un indice \n");
    scanf ("%d", &i);
    printf ("Ingrese un booleano para el resultado (0 para 'falso' y cualquier otro entero para 'verdadero') \n");
    scanf ("%d", &j);

    r = p2 (x, i, res ,j);

    return 0;
}

/* 
Estos son los estados en cada iteración del primer programa del ejercicio 5b) para el estado inicial x -> 13 y -> 3 i -> 0: 

x -> 10, y -> 3, i -> 1
x -> 7, y -> 3, i -> 2
x -> 4, y -> 3, i -> 3
x -> 1, y -> 3, i -> 4 

El programa me devuelve en su última iteración (siempre que 'x' sea igual o más chico que 'y') el cociente obtenido por dividr 'x' en 'y' en 'i'.
*/

/*
Estos son los estados en cada iteración del segundo programa del ejercicio 5b) para el estado inicial x -> 5 i -> 0 res -> 0:

x -> 5 i -> 3 res -> 1
x -> 5 i -> 4 res -> 1
x -> 5 i -> 5 res -> 1

El programa me devuelve en su última iteracion el número más chico que divide al entero 'x' asignando dicho divisor en 'i', si 'x' es impar y en 'i-1' si x es par.
*/