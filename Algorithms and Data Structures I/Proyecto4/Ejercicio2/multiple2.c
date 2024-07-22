#include <stdio.h>
#include <assert.h>

int pedirEntero(void)
{
    int x;

    printf("Ingrese un entero\n");
    scanf ("%d", &x);
    return x;
}

int main (void){

 printf("multiple2)\n");

 int x;
 int y;
 int z;
 int X;
 int Y;
 int Z;

 x = pedirEntero();
 y = pedirEntero();
 z = pedirEntero();
 X = x;
 Y = y;
 Z = z;

 assert(x == X && y == Y && z == Z);//{Pre: x = X, y = Y, z = Z}
 x = y;
 y = y + X + z;
 z = Y + X;
 assert(x == Y && y == Y + X + Z && z == Y + X);//{Post: x = Y, y = Y + X + Z, z = Y + X}

 printf("x -> %d y -> %d z -> %d\n",x,y,z);

 return 0;
}