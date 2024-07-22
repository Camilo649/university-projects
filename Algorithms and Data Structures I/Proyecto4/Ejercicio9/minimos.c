#include <stdio.h>
#include <limits.h>
#include <assert.h>
#define N 9

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
    assert(a[i] <= INT_MAX && a[i] >= INT_MIN);
    i = i + 1;
 }
}

int minimo_pares(int a[], int tam)
{
  int min_p;
  int i;

  min_p = INT_MAX;
  i = 0;

  while (i < tam)
  {
    if ((a[i]%2 == 0) && (a[i] <= min_p))
    {
        min_p = a[i];
        i = i+1;
    }
    else
    {
        i = i+1;
    }
  }

  return min_p;
}

int minimo_impares(int a[], int tam)
{
  int min_i;
  int i;

  min_i = INT_MAX;
  i = 0;

  while (i < tam)
  {
    if ((a[i]%2 != 0) && (a[i] <= min_i))
    {
        min_i = a[i];
        i = i+1;
    }
    else
    {
        i = i+1;
    }
  }

  return min_i;
}

int main(void)
{
    printf("Minimo\n");

    int a[N];

    pedirArreglo(a, N);

    int x, y, min;

    x = minimo_impares (a, N);
    y = minimo_pares (a, N);

    if (x >= y)
    {
        min = y;
    } 
    else 
    {
        min = x;
    }

    printf("El minimo elemento del arreglo ingresado es : %d\n", min);

    return 0;
}