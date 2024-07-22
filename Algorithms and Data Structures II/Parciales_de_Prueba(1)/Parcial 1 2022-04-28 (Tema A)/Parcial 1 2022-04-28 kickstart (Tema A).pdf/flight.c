/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 3;

Flight flight_from_file(FILE *file, char code)
{
    Flight flight;
    int res = 0;
    flight.code = code;

    res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT, &flight.type, &flight.hour, &flight.passengers_amount);
    if (res != AMOUNT_OF_FLIGHT_VARS)
    {
        fclose(file);
        fprintf(stderr, "Invalid file.\n");
        exit(EXIT_FAILURE);
    }
    
    return flight;
}
