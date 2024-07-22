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

 printf("Minimo\n");

 int x;
 int y;
 int m;

 x = pedirEntero();
 y = pedirEntero();

//{True} (Precondicion)
 if (x >= y)
 {
    m = y;
 } 
 else {
    m = x;
 }
 //{(x<y && m = x) || (x>=y && m = y)} (Postcondicion)
 assert((x<y && m == x) || (x>=y && m == y)); 
 
 printf("El minimo es: %d\n",m);

 return 0;  
}