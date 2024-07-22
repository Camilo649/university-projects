#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads a string given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * An integer value and one character per line is expected,"
           " where after the integer is expected to be an arrow consisting of the symbol - and then >." 
           " In addition, the input character is expected to be between two asterisk (*) symbols."
           "\n\n"
           "In other words, the file format is:\n"
           "<int> -> *<char>*\n"
           "<int> -> *<char>*\n"
           "<int> -> *<char>*\n"
           "(:)\n\n" 
           ,program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

//FUNCIÓN AUXILIAR: Dado un arreglo, devuelve true si existen elementos repetidos.
bool is_repeat(unsigned int a[], unsigned int length)
{
    unsigned int i = 0u;
    unsigned int j;
    bool res = false;
    while(i < (length-1) && !res)
    {
        j = (i+1);
        while (j < length && !res )
        {
            if (a[i] == a[j])
            {
            res = true;
            }
            ++j;
        }
        ++i;
    }
    
    return res;
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
    unsigned int current_length = 0u;
    FILE *f = fopen(path, "r");

    while (current_length < max_size && (feof(f) == 0))
    {
        fscanf (f, "%u -> *%c* \n", &indexes[current_length], &letters[current_length]);
        ++current_length;
    }
    if ((feof(f) == 0))
    {
        fprintf(stderr, "Capacidad maxima excedida *-*. No puede haber más de %u caracteres.\n", MAX_SIZE);
        exit(EXIT_FAILURE);
    }
    else if (is_repeat(indexes, current_length))
    {
        fprintf(stderr, "Por favor, no ingresar índices repetidos.\n");
        exit(EXIT_FAILURE);
    }
    fclose(f);

    return current_length;
}  

void reconstruir(unsigned int I[], char L[], char S[], unsigned int size) {
    for (unsigned int i = 0; i < size; i++)
    {
      if (I[i] >= size)
      {
        printf("Recordá indexar desde 0 hasta (n-1), donde 'n' es la cantidad total de caracteres. \n");
        exit(EXIT_FAILURE);
      }
      
      S[I[i]] = L[i];
    }
}

int main(int argc, char *argv[]) {
    filepath = parse_filepath(argc, argv);
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length = data_from_file(filepath, indexes, letters, MAX_SIZE); 
    reconstruir(indexes, letters, sorted, length);
    dump(sorted, length);

    return EXIT_SUCCESS;
}