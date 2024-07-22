/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */

#define POSSIBLE_OPTIONS 7

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n", program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);
       ++i;
    }
    fclose(file);
    return read_tree;
}

abb patter_matching(abb tree, unsigned int option){
    abb_elem elem=0;
    int res=0;

    if (option == 1)
    {
        if (!abb_is_empty(tree))
        {
            printf("\n");
            abb_dump(tree);
            printf("\n");
        }
        else
        {
            printf("\nÁrbol vacío\n");
        }
    }
    else if (option == 2)
    {
        printf("\n¿Qué elemento desea agregar?\n");
        res = scanf(" %d", &elem);
        if (res != 1) {
            printf("\nElemento inválido!\n");
        }
        tree = abb_add(tree, elem);
    }
    else if (option == 3)
    {
        if (abb_is_empty(tree))
        {
            printf("\nNo tiene sentido eliminarle cosas a algo que no las tiene desde un principio...\n");
        }
        else
        {
            printf("\n¿Qué elemento le gustaría eliminar?\n");
            res = scanf(" %d", &elem);
            if (res != 1) {
                printf("\nElemento inválido!\n");
            }
            tree = abb_remove(tree, elem);
        }
    }
    else if (option == 4)
    {
        if (abb_is_empty(tree))
        {
            printf("\nNo se puede buscar en árboles vacíos...\n");
        }
        else
        {
            printf("\nIngrese el elemento a chequear\n");
            res = scanf(" %d", &elem);
            if (res != 1) {
                printf("\nElemento inválido!\n");
            }
            if (abb_exists(tree, elem))
            {
                printf("\nEl elemento se encuentra en el árbol :)\n");
            }
            else
            {
                printf("\nNo pudimos encontrar el elemento :(\n");
            }
        }
    }
    else if (option == 5)
    {
        printf("\nEl tamaño del árbol es: %u \n", abb_length(tree));
    }
    else
    {
        if (!abb_is_empty(tree)) {
            printf("\n");
            printf("raiz: %d\nminimo: %d\nmaximo: %d\n", abb_root(tree), abb_min(tree), abb_max(tree));
        } else {
            printf("\nÁrbol vacío\n");
        }
    }
    
    return tree;
}

abb interfaz (abb tree){
    bool done=false;
    unsigned int option=0u;
    int res=0;

    printf("\nBienvenido a la interfaz para ABB (Árboles Binarios de Búsqueda)\n"
           "El árbol cargado es el siguiente:\n");
    if (!abb_is_empty(tree))
        {
            printf("\n");
            abb_dump(tree);
            printf("\n");
        }
        else
        {
            printf("\nÁrbol vacío\n");
        }
    while (!done)
    {
        printf("\n¿Qué te gustaría hacer ahora mismo?\n"
               "Para ver el arbol, ingrese 1\n"
               "Para agregar un elemento, ingrese 2\n"
               "Para eliminar un elemento, ingrese 3\n"
               "Para comprobar si un elemento se encuentra en el árbol, ingrese 4\n"
               "Para saber el tamaño del árbol, ingrese 5\n"
               "Para ver la raíz, el máximo y el mínimo del árbol, ingrese 6\n"
               "Si desea finalizar el programa, ingrese 7\n");
        res = scanf(" %u", &option);
        if (res != 1 || option > POSSIBLE_OPTIONS || option == 0u)
        {
            printf("\nPor favor, los números ingresados deben estar entre 1 y %u\n", POSSIBLE_OPTIONS);
        }
        else if (option == 7)
        {
            done = true;
        }
        else
        {
            tree = patter_matching(tree, option);
        }
    }

    return tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
    abb_dump(tree);
    if (!abb_is_empty(tree)) {
        printf("\n");
        printf("raiz: %d\nminimo: %d\nmaximo: %d\n", abb_root(tree), abb_min(tree), abb_max(tree));
    } else {
        printf("\nÁrbol vacío\n");
    }

    tree = interfaz(tree);

    tree = abb_destroy(tree);

    return (EXIT_SUCCESS);
}

/*
    Contestando a la pregunta "La función abb_dump() muestra por pantalla los elementos de manera ordenada. ¿Por qué se
    comporta de esta manera? ¿Cómo es el árbol que se obtiene agregando los elementos en el orden que
    muestra el contenido abb_dump()?"

    Por que las llamadas recursivas comienzan llamando por el lado izquierdo del árbol hasta toparse con NULL en la izquierda,
    solo ahí es cuando imprime y procede a llamarse recursivamente con el lado derecho hasta que llega a NULL.
    Si graficáramos el árbol que muestra abb_dump(), sería una diagonal que va creciendo de arriba a la izquiera para
    abajo a la derecha.
*/