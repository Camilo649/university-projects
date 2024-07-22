/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

static const int EXPECTED_DIM_VALUE = 2;

static const char *CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char *SEASON_NAMES[SEASONS] = {"low", "high"};

struct city_season
{
    int city;
    int season;
};

/**
 * @brief Calcula el costo total de elaborar 'product'.
 * @param[in] product Producto al que se le quiere calcular el costo de producción.
 */
static unsigned int costo_total_de_produccion(BakeryProduct product){

    return (product.flour_cant * product.flour_price) +
           (product.yeast_cant * product.yeast_price) +
           (product.butter_cant * product.butter_price);
}

/**
 * @brief Devuelve "true" si la combinación 'city'-'season' ya fue utilizada en 'array'.
 * @param[in] array Arreglo con las combinaciones ciudad-temporada.
 * @param[in] city Ciudad a chequear.
 * @param[in] season Temporada a chequear.
 * @param[in] length Cantidad de elementos del arreglo 'array'.
 */
static bool existe_combinacion(struct city_season* array, int city, int season, unsigned int length){
    bool existe=false;
    unsigned int i=0u;

    while (i<length && !existe)
    {
        existe = (array[i].city == city) && (array[i].season == season);
        ++i;
    }
    
    return existe;
}

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int best_profit(BakeryProductTable a)
{
    unsigned int max_profit = 0u;
    unsigned int costo = 0u;
    unsigned int ganancia = 0u;
    
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            costo = costo_total_de_produccion(a[city][season]);
            ganancia = a[city][season].sale_value - costo;
            if (ganancia > max_profit)
            {
                max_profit = ganancia;
            }
        }
    }

    return max_profit;
}

void array_from_file(BakeryProductTable array, const char *filepath)
{
    FILE *file = NULL;
    int city=0;
    int season=0;
    int res=0;
    //Arreglo auxiliar que guarda todas las combinaciones ciudad-temporada
    struct city_season* a=malloc(sizeof(struct city_season) * CITIES * SEASONS);
    unsigned int i=0u; 

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        free(a);
        a = NULL;
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    while (!feof(file))
    {
        res = fscanf(file, EXPECTED_CODE_FILE_FORMAT, &city, &season);
        if (res != EXPECTED_DIM_VALUE || city < 0 || season < 0)
        {
            fclose(file);
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        if (i!=0 && existe_combinacion(a, city, season, i))
        {
            free(a);
            a = NULL;
            fclose(file);
            fprintf(stderr, "No se pueden repetir combinaciones\n");
            exit(EXIT_FAILURE);
        }
        array[city][season] = bakery_product_from_file(file);
        a[i].city = city;
        a[i].season = season;
        ++i;
    }
    free(a);
    a = NULL;
    fclose(file);
}
