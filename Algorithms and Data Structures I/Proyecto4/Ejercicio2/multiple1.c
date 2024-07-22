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

 printf("multiple1)\n");

 int x;
 int y;
 int X;
 int Y;

 x = pedirEntero();
 y = pedirEntero();
 X = x;
 Y = y;
 
 assert (x == X && y == Y);//{Pre: x = X, y = Y}
 x = x + 1;
 y = X + y;
 assert (x == X + 1 && y == X + Y);//{Post: x = X + 1, y = X + Y}

 printf("x -> %d y -> %d\n",x,y);

 return 0;
}