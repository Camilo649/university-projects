#include <stdio.h>

int pedirEntero(void)
{
    int x;

    printf("Ingrese un entero\n");
    scanf ("%d", &x);
    return x;
}

void imprimeEntero(int x)
{
    printf("%d\n",x);
    return 0;
}

int main (void)

{
    printf ("Ejercicio 6a)\n");
    
    int x;
    
    x = pedirEntero();
    imprimeEntero (x);

    return 0;
}