#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

void pedirArreglo(int a[], unsigned int lenght){
 int x;
 for (size_t i = 0; i < lenght; i++)
 {
    printf("ingrese el elemento %d del arreglo\n",i);
    scanf ("%d", &x);
    a[i] = x;
 }
}

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
  struct bound_data res;
  res.is_lowerbound = true; //Inicializo las variables
  res.is_upperbound = true;
  res.exists = false;
  for (size_t i = 0; i < length; i++)
  {
    if (value >= arr[i] && res.is_upperbound) //Chequeo para ver si el valor puede ser considerado como cota inferior. Si en alguna ocasión ya no se cumple, no tiene sentido seguir comparando.
    {
      res.is_upperbound = true;
    }
    else
    {
      res.is_upperbound = false;
    }
    if (value <= arr[i] && res.is_lowerbound) //Chequeo para ver si el valor puede ser considerado como cota superior. Si en alguna ocasión ya no se cumple, no tiene sentido seguir comparando.
    {
      res.is_lowerbound = true;
    }
    else
    {
      res.is_lowerbound = false;
    }
    if (value == arr[i] && res.exists == false) //Me fijo si el valor pertenece al arreglo. Si se repite varias veces, guardo solo la posición de la primera aprición.
    {
      res.exists = true;
      res.where = i;
    }
  }
    return res;
}

int main(void) {
  int a [ARRAY_SIZE];
  int value;

  pedirArreglo(a, ARRAY_SIZE);
  printf("Introduzca el valor a comparar:\n");
  scanf("%d", &value);
    
  struct bound_data result = check_bound(value, a, ARRAY_SIZE);
  //POSIBLES SALIDAS:
  if (result.exists)
  {
    if (result.is_upperbound == result.is_lowerbound) 
    {
      printf("El arreglo solo contien el elemnto %d\n", value);
    }
    else if (result.is_upperbound)
    {
      printf("El valor ingresado es el máximo del arreglo y se encuentra en la posición %d del mismo\n", result.where);
    }
    else
    {
      printf("El valor ingresado es el mínimo del arreglo y se encuentra en la posición %d del mismo\n", result.where);
    }
  }
  else
  {
    if (result.is_upperbound == result.is_lowerbound) 
    {
      printf("El elemnto %d no es cota del arreglo ni pertenece al mismo\n", value);
    }
    else if (result.is_upperbound)
    {
      printf("El valor ingresado es una cota superior del arreglo\n");
    }
    else
    {
      printf("El valor ingresado es una cota inferior del arreglo\n");
    }
  }
  return EXIT_SUCCESS;
}