#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string.h"

#define TOLERANCE 20

int main(void)
{
    char user_input1[TOLERANCE];
    char user_input2[TOLERANCE];
    string str1;
    string str2;
    

    printf("\n"
           "---------------------\n"
           "COMPARADOR DE CADENAS\n"
           "---------------------\n\n");

    printf("Ingrese la primera cadena a comparar: ");
    str1 = string_create(fgets(user_input1, TOLERANCE, stdin));

    printf("Ingrese la segunda cadena a comparar: ");
    str2 = string_create(fgets(user_input2, TOLERANCE, stdin));

    printf("\nLas cadenas\n");
    string_dump(str1, stdout);
    printf(" y \n");
    string_dump(str2, stdout);
    if (string_eq(str1, str2))
    {
        printf("son iguales\n\n");
    }
    else
    {
        printf("son desiguales\n\n");

        string_dump(str1, stdout);
        string_less(str1, str2) ? printf("es menor alfabéticamente que\n") : 
                                  printf("es mayor alfabéticamente que\n");
        string_dump(str2, stdout);
    }
    
    string_destroy(str1);
    string_destroy(str2);
    
    return EXIT_SUCCESS;
}
