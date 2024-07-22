#include <stdio.h>
#define N 6

int sumatoria(int a[], int tam)
{
int i;
int x;
int s;

i = 0;
s = 0;

 while (i<tam)
 {
    printf("ingrese el elemento %d del arreglo\n",i);
    scanf ("%d", &x);
    a[i] = x;
    s = s + a[i]; 
    i = i + 1;
 }

 return s;
}

int main (void)
{

printf("Sumatoria)\n");

int a[N];

printf("El resultado es: %d\n",sumatoria(a, N));

return 0;
}