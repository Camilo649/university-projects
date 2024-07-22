#include <stdio.h>

int suma_hasta(int N)
{
   if (N >= 0)
   {
    N = (N * (N + 1)) / 2;
    printf("Resultado final: %d\n", N); 
   }
   else 
   {
       printf("ERROR FATAL!\n");
   }
   return N;   
}

int pedirEntero(void)
{
    int x;

    printf("Ingrese un entero\n");
    scanf ("%d", &x);
    return x;
}

int main (void){

printf("suma_hasta)\n");

suma_hasta(pedirEntero());

return 0;
}