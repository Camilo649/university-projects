/*
  @file weather_utils.h
  @brief Defines some operations on meteorological data
*/

#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include "array_helpers.h"

/**
 * @brief obtains lowest historical minimum temperature.
 * @param[in] a three-dimensional array containing the data
 * @return the lowest minimum temperature
 */
int min_historical_temp(WeatherTable a);

/**
 * @brief records for each year between 1980 and 2016 the highest maximum temperature during that year.
 * @param[in] a three-dimensional array containing the data
 * @param[out] out array with the max temperature for each year
 */
void max_temp_per_year(WeatherTable a, int out[YEARS]);

/**
 * @brief records for each year between 1980 and 2016 the month of that year in which the max monthly the highest monthly amount of precipitation was recorded in that year.
 * @param[in] a three-dimensional array containing the data
 * @param[out] out array with the months in which the max rainfall occurred for each year
 */
void months_with_max_prec_per_year(WeatherTable a, month_t out[YEARS]);

#endif //_WEATHER_UTILS_H