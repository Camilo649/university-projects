#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue_helpers.h"


queue queue_from_file(const char *filepath) {
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        fclose(file); //Esto es para que no quede sin liberar el archivo
        exit(EXIT_FAILURE);
    }
    int res = 0, empty_flag=0;
    res = fscanf(file, "empty: %d", &empty_flag);
    if (res != 1) {
        fprintf(stderr, "Invalid array.\n");
        fclose(file); //Esto es para que no quede sin liberar el archivo
        exit(EXIT_FAILURE);
    }
    queue q=queue_empty();
    while (!feof(file) && !empty_flag) {
        int value=0;
        res = fscanf(file," %d ", &value);
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            fclose(file); //Esto es para que no quede sin liberar el archivo
            exit(EXIT_FAILURE);
        }
        q = queue_enqueue(q, value);
    }
    fclose(file);
    return q;
}

//Nota: la modifiqué un poco para que el usuario elija con 1 al primer elemento de la cola, con 2 al segundo y así siguiendo.
queue queue_user_disscard(queue q) {
    unsigned int size=queue_size(q), disscard=0u;
    int res=0;
    assert(size > 0);
    printf("\n"
           "Eliminar n-esimo elemento\n"
           "-------------------------\n\n");
    queue_dump(q, stdout);
    do {
        printf("\nElija un elemento entre 1-%u: ", size);
        res=scanf("%u", &disscard);
        if (res != 1 || disscard > size || disscard == 0u) {
            printf("Elemento inválido!\n");
        }
    } while (disscard > size || disscard == 0u);
    if (res==1) {
        q = queue_disscard(q, disscard-1);
    }
    return res==1 ? q: NULL;
}
