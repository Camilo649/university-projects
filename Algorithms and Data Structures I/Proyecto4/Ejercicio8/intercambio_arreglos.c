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

void intercambiar(int a[], int tam, int i, int j)
{
    assert((tam > 0) && (0<= i && i<tam) && (0<= j && j<tam));

    int iaux;
    
    iaux = a[i];
    a[i] = a[j];
    a[j] = iaux;
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

 printf("entrada_salida\n");
 
 int tam;

 printf("ingrese una cantidad de elementos para el arreglo:\n");
 scanf("%d",&tam);
 
 int a[tam];

 pedirArreglo(a,tam);

 printf("Este es su arreglo actualmente: \n");

 imprimeArreglo(a,tam);

 int i, j;

 printf("Ingrese la posicion que desea intercambiar: \n");
 scanf("%d", &i);
 printf("Ingrese la posicion a la que desea mover el elemento: \n");
 scanf("%d", &j);

 intercambiar(a, tam, i, j);

 printf("Este es su arreglo despues del intercambio: \n");

 imprimeArreglo(a, tam);

 return 0;
}