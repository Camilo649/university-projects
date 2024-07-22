#include <stdio.h>
#include <limits.h>
#include <assert.h>
#define N 11

void pedirArreglo(float a[], int n_max)
{
 int i;
 float x;

 i = 0;
 while (i<n_max)
 {
    printf("ingrese el elemento %d del arreglo\n",i);
    scanf ("%f", &x);
    a[i] = x;
    assert(a[i] <= INT_MAX && a[i] >= INT_MIN);
    i = i + 1;
 }
}

struct datos_t {
float maximo;
float minimo;
float promedio;
};

struct datos_t stats(float a[], int tam)
{
    int i;
    struct datos_t d;

    i = 0;
    d.promedio = 0;
    d.maximo = INT_MIN;
    d.minimo = INT_MAX;

    while (i<tam)
    {
        if (a[i]>=d.maximo)
        {
            d.maximo = a[i];
        };
        if (a[i]<=d.minimo)
        {
            d.minimo = a[i];
        };
        
        d.promedio = d.promedio + a[i];
        i = i+1;
    }
    d.promedio = (d.promedio / tam);

    return d;
}

int main(void)
{
    printf("Stats \n");

    float a[N];

    struct datos_t d;

    pedirArreglo(a, N);

    d = stats(a, N);
    
    printf("Las estadisticas del estado son:\n Elemento Maximo = %f\n Elemento Minimo = %f\n Promedio = %f\n", d.maximo, d.minimo, d.promedio);

    return 0;
}