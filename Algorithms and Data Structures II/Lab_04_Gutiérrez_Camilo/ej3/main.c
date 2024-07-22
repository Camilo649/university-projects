/* First, the standard lib includes, alphabetically ordered */
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "list.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100000u;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Compute average for the list of numbers in file.\n"
           "\n",
           program_name);
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

float average(list l) {
    float r;
    unsigned int l_length;
    list l_copy;

    r = 0.0;
    l_length = length_list(l);
    l_copy = copy_list(l);
    while (!is_empty_list(l_copy))
    {
        r = r + head_list(l_copy);
        l_copy = tail_list(l_copy);
    }
    destroy_list(l_copy);
    
    return r/l_length;

}

/*
VERSIÓN CON ÍNDICES:
float average2(list l){
    float r;
    unsigned int l_length;

    r = 0.0;
    l_length = length(l);
    for (unsigned int i = 0u; i < l_length; ++i)
    {
        r = r + index(l, i);
    }

    return r/l_length;
}
*/

list array_to_list(int array[], unsigned int length) {
    list l;

    l = empty_list();
    for (unsigned int i = 0u; i < length; ++i) {
        l = addr_list(l, array[i]); //Como no me importa el orden, también podría usar addl.
    }

    return l;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    //FILE *file = NULL; ¿Puede ser que esté demás?

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* show the array in the screen */
    array_dump(array, length);

    /* transform from array to our list type */
    list l = array_to_list(array, length);

    /* call the average function */
    printf("The average is: %.2f \n", average(l));

    l = destroy_list(l);

    return (EXIT_SUCCESS);
}