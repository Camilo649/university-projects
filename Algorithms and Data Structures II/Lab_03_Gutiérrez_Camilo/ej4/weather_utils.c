/*
  @file weather_utils.c
  @brief Implements some operations on meteorological data
*/

#include <stdlib.h>
#include <limits.h>
#include "weather_utils.h"

int min_historical_temp(WeatherTable a)
{
    int current_min_temp = INT_MAX;

    for (unsigned int y = 0u; y < YEARS; ++y){
        for (month_t m = january; m <= december; ++m){
            for (unsigned int d = 0u; d < DAYS; ++d)
            {
                if (current_min_temp > a[y][m][d]._min_temp)
                {
                    current_min_temp = a[y][m][d]._min_temp;
                }
            }
        }
    }
    return current_min_temp;
}

void max_temp_per_year(WeatherTable a, int out[YEARS])
{
    int max_temp_current_year;

    for (unsigned int y = 0u; y < YEARS; ++y){
        max_temp_current_year = INT_MIN;
        for (month_t m = january; m <= december; ++m){
            for (unsigned int d = 0u; d < DAYS; ++d)
            {
                if (max_temp_current_year < a[y][m][d]._max_temp)
                {
                    max_temp_current_year = a[y][m][d]._max_temp;
                }
            }
        }
        out[y] = max_temp_current_year;
    }
}

void months_with_max_prec_per_year(WeatherTable a, month_t out[YEARS])
{
    month_t month_of_the_year_with_maxRainfall;
    unsigned int monthly_maxRainfall;
    unsigned int current_month_rainfall;

    for (unsigned int y = 0u; y < YEARS; ++y){
        monthly_maxRainfall = 0;
        for (month_t m = january; m <= december; ++m){
            current_month_rainfall = 0;
            for (unsigned int d = 0u; d < DAYS; ++d)
            {
                current_month_rainfall = current_month_rainfall + a[y][m][d]._rainfall;
            }
            if (monthly_maxRainfall < current_month_rainfall) //Si dos o más meses tienen la misma cantidad de precipitaciones mensuales, se guardara en el arreglo out el primero. Esto gracias al menor estricto.
                {
                    monthly_maxRainfall = current_month_rainfall;
                    month_of_the_year_with_maxRainfall = m;
                }
        }
        out[y] = month_of_the_year_with_maxRainfall;
    }
}