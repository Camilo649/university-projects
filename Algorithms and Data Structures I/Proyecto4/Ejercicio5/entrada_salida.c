#include <stdio.h>
#include <assert.h>

void pedirArreglo(int a[], int n_max)
{
 int i;
 int x;

 i = 0;
 while (i<n_max)
 {
    printf("ingrese el elemento %d del arreglo\n",i);
    scanf ("%d", &x);
    a[i] = x;
    i = i + 1;
 }
}

void imprimeArreglo(int a[], int n_max) 
{ 
 int i;
 
 i = 0;
 while (i<n_max)
 {
    printf("%d\n",a[i]);
    i = i + 1;
 }
 
}

int main (void){

 printf("entrada_salida)\n");
 
 int n_max;

 printf("ingrese una cantidad de elementos para el arreglo:\n");
 scanf("%d",&n_max);
 assert(n_max > 0);
 
 int a[n_max];

 pedirArreglo(a,n_max);

 printf("Este es el arreglo ingresado: \n");

 imprimeArreglo(a,n_max);

 return 0;
}