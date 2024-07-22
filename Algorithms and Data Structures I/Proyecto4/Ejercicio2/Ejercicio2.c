#include <stdio.h>

int pedirEntero(void)
{
    int x;

    printf("Ingrese un entero\n");
    scanf ("%d", &x);
    return x;
}

int main (void){

 printf("Ejercicio 2a)\n");

 int x;
 int y;
 int z;

 x = pedirEntero();
 y = pedirEntero();
 
 //{Pre: x = X, y = Y}
 x = x + 1;
 y = x + y;
 //{Post: x = X + 1, y = X + Y}

 printf("x -> %d y -> %d\n",x,y);

 x = pedirEntero();
 y = pedirEntero();
 z = pedirEntero();

 //{Pre: x = X, y = Y, z = Z}
 x = y;
 y = y + x + z; 
 z = y + x;
 //{Post: x = Y, y = Y + X + Z, z = Y + X}

 printf("x -> %d y -> %d z -> %d\n",x,y,z);

 return 0;
}