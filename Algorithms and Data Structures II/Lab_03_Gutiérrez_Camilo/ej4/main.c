/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "weather_utils.h"

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Load climate data from a given file in disk.\n"
           "\n"
           "The input file must exist in disk and every line in it must have the following format:\n\n"
           "<year> <month> <day> <temperature> <high> <low> <pressure> <moisture> <precipitations>\n\n"
           "Those elements must be integers and will be copied into the multidimensional integer array 'a'.\n"
           "The dimensions of the array are given by the macro tclimate.\n"
           "\n\n",
           program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 */
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

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    int min_temp, max_temp_by_year[YEARS];
    month_t months_with_max_prec_by_year[YEARS];
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array with the type of tclimate */
    WeatherTable array;

    /* parse the file to fill the array and obtain the actual length */
    array_from_file(array, filepath);

    /* store in min_temp the lowest historical temperature  */
    min_temp = min_historical_temp(array);

    /* show min_temp value */
    printf("La temperatura más baja registrada en grados centígrados de la provincia de Córdoba entre los años 1980-2016 fue de %d décimas.\n\n", min_temp);

    /* write in each element of max_temp_by_year the highest temperature with respect to the corresponding year */
    max_temp_per_year(array, max_temp_by_year);

    /* show the ordered array in the screen */
    printf("El siguiente arreglo contiene la mayor temperatura registrada en décimas de grados centígrados de la provincia de Córdoba durante los años 1980-2016 respectivamente:\n");
    array_dump_Lab02_v1(max_temp_by_year, YEARS);

    /* write in each element of months_with_max_prec_by_year the month with the highest monthly precipitation recorded in the corresponding year */
    months_with_max_prec_per_year(array, months_with_max_prec_by_year);

    /* show the ordered array in the screen */
    printf("El siguiente arreglo contiene el mes con la mayor precipitación mensual registrada en centécimas de milímetros de la provincia de Córdoba durante los años 1980-2016 respectivamente:\n");
    array_dump_Lab02_v2(months_with_max_prec_by_year, YEARS);    

    /* show the ordered array in the screen */
    array_dump(array);

    return (EXIT_SUCCESS);
}

/*
    Contestando a la pregunta: ¿Qué se puede observar en la salida del programa? cuando compilamos el código original sin el flag -Werror.
    Al compilar de esta forma, si bien los índices de la fecha ([YEARS][MONTHS][DAYS]) cargan como corresponde, los valores de las medidas climáticas asociados al arreglo están en su gran mayoría en 0 o, sobretodo los últimos, tienen números grandes como valores (no termino de entender porque sucede bien esto). 
*/