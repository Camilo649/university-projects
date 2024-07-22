#include "array_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    unsigned int size;
    FILE *f;

    f = fopen(filepath, "r"); //Abro el archivo y se lo asigno a mi variable "f".
    fscanf(f, "%u", &size); //Escaneo el primer entero del archivo. En este caso, la longitud del arreglo.
    for (unsigned int i = 0; i < size; i++)//Escaneo uno por uno los enteros después del salto de línea y los coloco dentro del arreglo en su posición correspondiente.
    {
        fscanf(f, "%d", &array[i]);
    }
    if (feof(f) != 0 || size > max_size) //Este if soluciona el problema para el caso "example-invalid.in" y cuando se lee un tamaño del arreglo mayor al estipulado.
        {
            printf("La longitud del arreglo no es acorde a su cantidad de elementos.");
            exit(EXIT_FAILURE);
        }
    fclose(f);

    return size;
}

void array_dump(int a[], unsigned int length) {
    /*int longitud = sizeof(a) / sizeof(a[0]);*/

    if (length == 0) //Comprueba si el arreglo es vacío.
    {
        printf("[] \n"); //Output para un arreglo vacío.
    }
    else //De no ser vacío imprime una vez los corchetes, donde el corchete del final va con el último elemento, y dentro de ellos rellena el arreglo escaneando uno por uno los números del fichero colocándolos en su posición correspondiente.
    {
        printf("[ "); 
    for (unsigned int i = 0; i < length - 1; i++)
    {
        printf("%d, ", a[i]);
    }  
    printf("%d] \n", a[length-1]); 
    }
}

bool array_is_sorted(int a[], unsigned int length) {
    unsigned int i = 0; //Incializo las variables
    bool sorted = true;

    while (i < (length - 1) && sorted) //Comparo cada elemento del arreglo con el siguiente (a excepción del último) buscando que no estén organizados de forma creciente en alguna parte para así poder dejar de iterar y devolver false como resultado. Caso contrario, realizo lenght-1 comparaciones y la función devuelve true.
    {
        if (a[i] > a[i + 1])
        {
            sorted = false;
        }
        i = i + 1;
    }
    return sorted;
}

void array_swap(int a[], unsigned int i, unsigned int j) {
    int aux = a[i];
   
    a[i] = a[j];
    a[j] = aux;
}

void array_invert(int a[], unsigned int lenght) {
    unsigned int i = 0;
    unsigned int j = lenght - 1;
    
    while (i < lenght / 2 && j >= lenght / 2)
    {
        array_swap(a, i, j);
        i = i + 1;
        j = j - 1;
    }
}