#include <stdio.h>

void imprimeHola(void)
{
    printf("hola\n");
}

void imprimeChau(void)
{
    printf("chau\n");
}

int main (void)

{
    printf ("Ejercicio 6c)\n");

imprimeHola(), imprimeHola();
imprimeChau(), imprimeChau();

    return 0;
}