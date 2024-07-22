/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_stdin(int array[], unsigned int max_size) {
    FILE *f;
    unsigned int size;

    f = stdin;
    fprintf(stdout, "Por favor, ingrese el tamaño de su arreglo: ");
    fscanf(f, "%u", &size);
    if (size > max_size)
    {
        fprintf(stdout, "Error al escanear.\n" 
                        "Valor máximo aceptado = 100000.\n"
                        "(Revisa no estar ingresando valores negativos).\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (unsigned int i = 0; i < size; i++)
        {
        fprintf(stdout, "Ingrese un entero para la posición %d del arreglo: \n", i);
        fscanf(f, "%d", &array[i]);
        }
    }
    
    return size;
}

void array_dump(int a[], unsigned int length) {
    if (length == 0)
    {
        fprintf(stdout, "That´s your empty array ---> []");
    }
    else
    {
        fprintf(stdout, "[ "); 
        for (unsigned int i = 0; i < length - 1; i++)
        {
            fprintf(stdout, "%d, ", a[i]);
        }  
        fprintf(stdout, "%d]", a[length - 1]); 
    }
}


int main() {
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}