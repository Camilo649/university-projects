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

 printf("Absoluto\n");

 int x;

 x = pedirEntero();

// {True} (Precondicion)
 if(x >= 0)
 {
    x = x;
 }
 else
 {
    x = -x;
 }
// {x>=0} (Postcondicion)
assert(x>=0);

 printf("El valor absoluto es: %d\n", x);

 return 0;
}