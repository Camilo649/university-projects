/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include <stdbool.h>
#include "flight.h"
#include "array_helpers.h"

static const int AMOUNT_OF_FLIGHT_VARS = 2;

static bool is_valid_hour(unsigned int hour){

    return (hour != 0) && (hour <= HOURS);
}

Flight flight_from_file(FILE *file, char code, item_t type)
{
    Flight flight;
    flight.code = code;
    flight.type = type;
    int res = 0;

    res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT, &flight.hour, &flight.items_amount);
    if (res != AMOUNT_OF_FLIGHT_VARS || !is_valid_hour(flight.hour))
    {
        fclose(file);
        fprintf(stderr, "Invalid file.\n");
        exit(EXIT_FAILURE);
    }

    return flight;
}
