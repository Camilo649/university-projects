/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

static const int AMOUNT_OF_CODE_VAR = 1;

struct type_hour
{
    item_t type;
    unsigned int hour;
};

typedef struct type_hour Combinations[TYPE][HOURS];

/**
 * @brief returns true when reach last entry in flight table
 * @return True when is the last entre of the flight table, False otherwise
 */
static bool is_last_line(unsigned int hour, unsigned int type)
{
    return hour == HOURS - 1u && type == TYPE - 1u;
}

static unsigned int calculate_cost(unsigned int items_cant, item_t type){

    return (items_cant - (type == 0 ? MAX_ALLOWED_BOXES : MAX_ALLOWED_LETTERS)) * 
           (type == 0 ? BOX_PENALTY : LETTER_PENALTY);
}

static bool valid_combination(Combinations a, unsigned int hour, item_t type, unsigned int lines){
    bool is_valid = true;
    unsigned int line=0u;

    while (line<lines && is_valid)
    {
        is_valid = (a[type][line].type != type) || (a[type][line].hour != hour);
        ++line;
    }
       
    
    

    return is_valid;
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

unsigned int extra_space_fee_cost(DeliveryTable a)
{
    unsigned int total_cost=0u;
    unsigned int items_cant=0u;

    for (unsigned int type = 0u; type < TYPE; ++type) {
        items_cant = 0u;
        for (unsigned int hour = 0u; hour < FEE_CLOSE_HOUR; ++hour) {
            items_cant = items_cant + a[type][hour].items_amount;
        }
        if (items_cant > (type == 0 ? MAX_ALLOWED_BOXES : MAX_ALLOWED_LETTERS))
        {
            total_cost = total_cost + calculate_cost(items_cant, type);
        }
    }

    return total_cost;
}

void array_from_file(DeliveryTable array, const char *filepath)
{
    FILE *file = NULL;
    char code;
    int res = 0;
    unsigned int line = 0u;
    Combinations used_combinations;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(file))
    {
        res = fscanf(file, EXPECTED_CODE_FILE_FORMAT, &code);
        if (res != AMOUNT_OF_CODE_VAR)
        {
            fclose(file);
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }

        Flight flight_boxes = flight_from_file(file, code, boxes);
        Flight flight_letters = flight_from_file(file, code, letters);
        array[boxes][flight_boxes.hour - 1] = flight_boxes;
        if (!valid_combination(used_combinations, flight_boxes.hour, boxes, line))
        {
            fclose(file);
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        used_combinations[boxes][line].type=boxes;
        used_combinations[boxes][line].hour=flight_boxes.hour;
        if (!valid_combination(used_combinations, flight_letters.hour, letters, line))
        {
            fclose(file);
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        array[letters][flight_letters.hour - 1] = flight_letters;
        used_combinations[letters][line].type=letters;
        used_combinations[letters][line].hour=flight_letters.hour;
        ++line;
    }
    //Al contemplar 24 horas, el archivo solo puede tener 24 líneas. 
    if (line != HOURS)
    {
        fclose(file);
        fprintf(stderr, "Invalid file.\n");
        exit(EXIT_FAILURE);
    }
}
