#include <stdio.h>
#include <assert.h>

int pedirCantidadDeSaludos(void)
{
    int x;

    printf("¿Saludar cuantas veces?\n");
    scanf ("%d", &x);
    assert(x > 0);
    return x;
}

void holaHasta(int n){

    while (n != 0)
    {
        printf("Hola\n");
        n = n-1;
    }
}

int main (void){

 printf("Ejercicio 1\n");

 holaHasta(pedirCantidadDeSaludos());

 return 0;  
}