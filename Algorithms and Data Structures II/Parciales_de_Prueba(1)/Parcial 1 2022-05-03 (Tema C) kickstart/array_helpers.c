/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
 * @brief returns true when reach last entry in flight table
 * @return True when is the last entre of the flight table, False otherwise
 */
static bool is_last_line(unsigned int hour, unsigned int type)
{
    return hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a)
{
    for (unsigned int type = 0u; type < TYPE; ++type)
    {
        for (unsigned int hour = 0u; hour < HOURS; ++hour)
        {
            Flight f = a[type][hour];
            fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
            if (!is_last_line(hour, type))
            {
                fprintf(stdout, "\n");
            }
        }
    }
}

unsigned int extra_space_fee_cost(DeliveryTable a, unsigned int h)
{
    unsigned int extra_fee;
    unsigned int current_allowed_boxes;
    unsigned int current_allowed_letters;

    current_allowed_boxes = 0u;
    current_allowed_letters = 0u;
    for (unsigned int hour = 0u; hour <= h; ++hour)
    {
        current_allowed_boxes = current_allowed_boxes + a[boxes][hour].items_amount;
        current_allowed_letters = current_allowed_letters + a[letters][hour].items_amount;
    }
    extra_fee = 0u;
    if (current_allowed_boxes > MAX_ALLOWED_BOXES)
    {
        for (unsigned int extra_allowed_boxes = current_allowed_boxes - MAX_ALLOWED_BOXES; extra_allowed_boxes > 0; --extra_allowed_boxes)
        {
            extra_fee = extra_fee + BOX_PENALTY;
        }
    }
    if (current_allowed_letters > MAX_ALLOWED_LETTERS)
    {
        for (unsigned int extra_allowed_letters = current_allowed_letters - MAX_ALLOWED_LETTERS; extra_allowed_letters > 0; --extra_allowed_letters)
        {
            extra_fee = extra_fee + LETTER_PENALTY;
        }
    }

    return extra_fee;
}

void array_from_file(DeliveryTable array, const char *filepath)
{
    FILE *file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    char code;
    unsigned int arrival_hour;
    int i = 0;
    while (!feof(file))
    {
        int res = fscanf(file, " _%c_ ", &code);
        if (res != 1u)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        res = fscanf(file, " %u ", &arrival_hour);
        if (res != 1u)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        /* COMPLETAR: Generar y guardar ambos Flight en el array multidimensional */
        Flight flight_boxes = flight_from_file(file, code, arrival_hour);
        Flight flight_letters = flight_from_file(file, code, arrival_hour);
        array[boxes][arrival_hour - 1] = flight_boxes;
        array[letters][arrival_hour - 1] = flight_letters;
        ++i;
    }
    fclose(file);
}
