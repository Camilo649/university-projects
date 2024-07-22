#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#define N 7

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

bool existe_positivo(int a[], int tam)
{ 
  pedirArreglo (a, N);

  int i;
  bool res;
  i = 0;
  res = false;

  while (i<tam && !res)
  {
    if (a[i]>=0)
    {
        res = true;
        printf("%d (verdadero)\n",res);
        return 0;
    }
    else 
    {
        i = i + 1;
    }
  }

printf("%d (falso)\n", res);
return 0;
}

bool todos_positivos(int a[], int tam)
{
  pedirArreglo (a, N);
  int i;
  bool res;
  i = 0;
  res = true;

  while (i<tam && res)
  {
    if (a[i]<0)
    {
        res = false;
        printf("%d (falso)\n",res);
        return 0;
    }
    else 
    {
        i = i + 1;
    }
  }

printf("%d (verdadero)\n", res);
return 0;
}

int main (void)
{
printf("Positivos\n");

int a[N];
int decision;

printf("Para saber si existe un positivo en el arreglo ingrese (0).\nPara saber si todos los elementos del arreglo son positivos, ingrese (1).\n");
scanf("%d", &decision);
assert((decision == 0) || (decision == 1));

if (decision == 0)
{
    existe_positivo(a, N);
}
else
{
    todos_positivos(a, N);
}

return 0;
}