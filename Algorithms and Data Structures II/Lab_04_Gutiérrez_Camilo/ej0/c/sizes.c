#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 35, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n", sizeof(messi.name),
                                       sizeof(messi.age),
                                       sizeof(messi.height),
                                       sizeof(messi));

    return EXIT_SUCCESS;
}

/*
    Contestnado a la pregunta: "¿La suma de los miembros coincide con el total? ¿El tamaño del campo name depende del nombre que contiene?"
    La respuesta es no y no. La suma de los miembros es 30 bytes + 4 bytes + 4 bytes = 38 bytes y el total es de 40 bytes.
    El campo name reserva memoria en base a la macro NAME_MAXSIZE, puesto que está implementado como un arreglo de chars. Como la macro es 30 y cada char ocupa 1 byte, el tamaño del campo name será siempre de 30 bytes independientemente de la cantidad y variedad de chars que allí se encuentren. 
*/