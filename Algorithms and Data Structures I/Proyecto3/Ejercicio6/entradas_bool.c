#include <stdio.h>
#include <stdbool.h>

bool pedirBooleano(void)
{
    bool x;
    int j;
    printf("Ingrese un booleano (0 para 'falso' y cualquier otro entero para 'verdadero')\n");
    scanf ("%d", &j);
    x = j;
    return x;
}

void imprimeBooleano(bool x)
{
    if(x==true)
        printf("Verdadero\n");
    else
        printf("Falso\n");
    return 0;
}

int main (void)

{
    printf ("Ejercicio 6b)\n");
    
    bool x;
    int j;
    
    j = pedirBooleano();
    imprimeBooleano (j);

    return 0;
}