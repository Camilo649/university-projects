#include <stdio.h>

int pedirEntero(char y)
{
    int x;
    printf("Ingrese un entero %c :\n", y);
    scanf("%d", &x);
    return x;
}

int inciso4b(void)
{
    int x = pedirEntero('x');
    int y = pedirEntero('y');
    int z = pedirEntero('z');
    int m = pedirEntero('m');

    if (x < y)
    {
       m = x;
       printf("x -> %d y -> %d z -> %d m -> %d\n",x,y,z,m);
    }
    else
    {
        m = y;
        printf("x -> %d y -> %d z -> %d m -> %d\n",x,y,z,m); 
    }
    if (m < z)
    {
        printf("x -> %d y -> %d z -> %d m -> %d\n",x,y,z,m); 
    }
    else 
    {
        m = z;
        printf("x -> %d y -> %d z -> %d m -> %d\n",x,y,z,m);
    }
    return 0;
}

int main(void)
{
    inciso4b();
    return 0;
}

/* -Usando estas funciones podemos escribir un codigo mas acortado.

   -Se podria escribir una funcion que calcule el minimo entre 3 numeros.

   -pedirEntero y pedirBooleano se podria usar en en todos los ejerecicios siempre y cuando se trate de ingresar valores a las variables */