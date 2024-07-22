#include <stdio.h>
#include <assert.h>

int main (void){

 printf("Intercambio de Variables\n");
 
 int x;
 int y;
 int z;

 printf("Ingrese valor para la variable x\n");
 scanf ("%d", &x);
 printf("Ingrese valor para la variable y\n");
 scanf ("%d", &y);

 //{True} (Precondicion)
 z = x;
 //{z == x}
 assert(z == x);
 x = y;
 //{x == y}
 assert(x == y);
 y = z;
 //{y == z} (Postcondicion)
 assert(y == z);

 printf("x -> %d y -> %d\n",x,y);

 return 0; 
}