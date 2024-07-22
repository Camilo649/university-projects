/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //Incluyo esta librería para poder usar un valor como infinito

#include "array_helpers.h"

#define EXPECTED_CODE_FILE_FORMAT " ##%u\?\?%u "
static const int EXPECTED_DIM_VALUE = 2;

static const char *CITY_NAMES[CITIES] = {"Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char *SEASON_NAMES[SEASONS] = {"Low", "High"};

struct citySeason
{
    unsigned int city;
    unsigned int season;
};

/**
 * @brief Calcula el costo total de produccion.
 * @param[in] b matriz con los datos de las panaderías.
 */
static unsigned int costo_de_producir(BakeryProduct b){
    unsigned int costo=0u;

    costo = (b.flour_price * b.flour_cant) + (b.butter_price * b.butter_cant) + (b.yeast_price * b.yeast_cant);

    return costo; 
}

/**
 * @brief Devuelve "true" si la combinacion city, season ya fue utilizada.
 * @param[in] array arreglo con las combinaciones ciudades-temporada ya usadas.
 * @param[in] length longitud de array.
 * @param[in] city ciudad a buscar.
 * @param[in] season temporada a buscar. 
 */
static bool combinacion_usada(struct citySeason* array, unsigned int length, unsigned int city, unsigned int season){
    bool exist = false;
    unsigned int i=0u;

    while (i<length && !exist)
    {
        exist = (array[i].city == city) && (array[i].season == season);
        ++i;
    }

    return exist;
}

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in season %s: Yeast (%u,%u) Butter (%u,%u) flour (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int worst_profit(BakeryProductTable a)
{
    unsigned int menor_ganancia=INT_MAX;
    unsigned int costo=0u;
    unsigned int ganancia=0u;

    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            costo = costo_de_producir(a[city][season]);
            ganancia = a[city][season].sale_value - costo;
            if (ganancia < menor_ganancia)
            {
                menor_ganancia = ganancia;
            }
        }
    }

    return menor_ganancia;
}

void array_from_file(BakeryProductTable array, const char *filepath)
{
    FILE *file=NULL;
    unsigned int ciudad=0u;
    unsigned int temporada=0u;
    int res=0;
    struct citySeason* Chequeador=malloc(sizeof(struct citySeason) * CITIES * SEASONS); //Arreglo auxiliar que guarda las combinaciones ciudad-temporada ya utilizadas
    unsigned int current_length=0u;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(file))
    {
        res = fscanf(file, EXPECTED_CODE_FILE_FORMAT, &ciudad, &temporada);
        if (res != EXPECTED_DIM_VALUE || ciudad > 4 || temporada > 1)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        if (combinacion_usada(Chequeador, current_length, ciudad, temporada))
        {
            fprintf(stderr, "No se pueden repetir combinaciones del tipo ciudad-temporada.\n");
            exit(EXIT_FAILURE);
        }
        Chequeador[current_length].city = ciudad;
        Chequeador[current_length].season = temporada;
        ++current_length;
        array[ciudad][temporada] = bakery_product_from_file(file);
    }
    free(Chequeador);
    Chequeador = NULL;
    fclose(file);
}
