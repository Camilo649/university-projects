#include <stdio.h>
#define N 10

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

int pedirEntero(void)
{
    int x;

    printf("Ingrese el entero a comparar: \n");
    scanf ("%d", &x);
    return x;
}

struct comp_t {
int menores;
int iguales;
int mayores;
};

struct comp_t cuantos(int a[], int tam, int elem)
{
    int i;
    struct comp_t cant;
    
    cant.menores = 0;
    cant.iguales = 0;
    cant.mayores = 0;
    i = 0;

    while (i<tam)
    {
        if (a[i]<elem)
        {
            cant.menores = cant.menores+1;
        }
        else if (a[i]==elem)
        {
            cant.iguales = cant.iguales+1;
        }
        else
        {
            cant.mayores = cant.mayores+1;
        }
        i = i+1; 
    }

    printf("En el arreglo hay %d elementos menores a %d, %d elementos iguales a %d y %d elementos mayores a %d\n", cant.menores, elem, cant.iguales, elem, cant.mayores, elem);

    return cant;
}

int main(void)
{
    printf("Cuantos\n");

    int a[N];

    pedirArreglo(a, N);

    cuantos(a, N, pedirEntero());

    return 0;
}