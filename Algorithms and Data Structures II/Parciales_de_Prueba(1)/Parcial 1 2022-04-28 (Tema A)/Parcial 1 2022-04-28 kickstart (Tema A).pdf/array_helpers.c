/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

static const int AMOUNT_OF_FLIGHT_CODE_VARS = 1;

//Tipo de datos auxiliar para chequear que no haya más de una llegada o salida en una misma hora.
typedef unsigned int Combinations [HOURS];

/**
 * @brief returns true when reach last entry in flight table
 * @return True when is the last entry of the flight table, False otherwise
 */
static bool is_last_line(unsigned int hour, unsigned int type)
{
    return hour == HOURS - 1u && type == TYPE - 1u;
}

/**
 * @brief Devuelve 'true' si 'hour' está dentro del rango válido delimitado por las condiciones.
 * @param[in] hour hora a chequear
 */
static bool is_valid_hour(unsigned int hour){

    return (hour != 0u) && (hour <= 24u);
}

/**
 * @brief Cálcula cuntos pasajeros están esperando.
 * @param[in] actual_waiting_passengers pasajeros que actualmente están esperando
 * @param[in] departure_passengers pasajeros que viajan en el próximo vuelo
 */
static unsigned int calculate_waiting_passengers(unsigned int actual_waiting_passengers, unsigned int departure_passengers){

    return actual_waiting_passengers - departure_passengers;
}

/**
 * @brief Devuelve 'true' si 'hour' ya había aparecido anteriormente en 'c'.
 * @param[in] c arreglo con las horas ya ocupadas
 * @param[in] hour hora a chequear
 * @param[in] length cantidad de elementos de 'c'
 */
static bool hour_used(Combinations c, unsigned int hour, unsigned int length){
    bool used=false;
    unsigned int h=0u;

    while (h<length && !used)
    {
        used = (c[h] == hour);
        ++h;
    }

    return used;
}

void array_dump(LayoverTable a)
{
    for (unsigned int hour = 0u; hour < HOURS; ++hour)
    {
        for (unsigned int type = 0u; type < TYPE; ++type)
        {
            Flight f = a[hour][type];
            fprintf(stdout, "%c: %s at %u:00 with %u passengers", f.code, f.type == 0 ? "arrives" : "departs", f.hour - 1, f.passengers_amount);
            if (!is_last_line(hour, type))
            {
                fprintf(stdout, "\n");
            }
        }
    }
}

unsigned int passengers_amount_in_airport (LayoverTable a, unsigned int h) {
   assert(is_valid_hour(h)); //PRE
   unsigned int waiting_passengers=0u;

    for (unsigned int hour = 0u; hour < (h - 1); ++hour)
    {
        assert(waiting_passengers + a[hour][arrival].passengers_amount >= 
               a[hour][departure].passengers_amount); //Invariante
        waiting_passengers = calculate_waiting_passengers(waiting_passengers + a[hour][arrival].passengers_amount,
                                                          a[hour][departure].passengers_amount);
    }

    /*Devuelvo los pasajeros en espera hasta la hora (h - 1) más los pasajeros que llegaron a esa hora.*/
    return waiting_passengers + a[h][arrival].passengers_amount;
}

void array_from_file(LayoverTable array, const char *filepath)
{
    FILE *file = NULL;
    char code;
    int line = 0;
    Combinations ocuped_arrival_hours;
    Combinations ocuped_departure_hours;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    while (!feof(file) && line <= HOURS)
    {
        int res = fscanf(file, EXPECTED_FLIGHT_CODE_FILE_FORMAT, &code);
        if (res != AMOUNT_OF_FLIGHT_CODE_VARS || code == '_')
        {
            fclose(file);
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        Flight flight_arrival = flight_from_file(file, code);
        Flight flight_departure = flight_from_file(file, code);
        if (flight_arrival.type != arrival || flight_departure.type != departure)
        {
            fclose(file);
            fprintf(stderr, "Las primeras tres columnas siempre deben ser de tipo 'llegada'" 
                            " y las segundas tres columnas siempre del tipo 'partida'\n");
            exit(EXIT_FAILURE);
        }
        if (!is_valid_hour(flight_arrival.hour) || !is_valid_hour(flight_departure.hour))
        {
            fclose(file);
            fprintf(stderr, "El ragno horario que el archivo debe contener va desde 1 hasta %u inclusive.\n",
                            HOURS);
            exit(EXIT_FAILURE);
        }
        if (flight_arrival.hour > flight_departure.hour)
        {
            fclose(file);
            fprintf(stderr, "Un vuelo, a lo sumo, puede salir en el mismo horario en el que llegó.\n");
            exit(EXIT_FAILURE);
        }
        if (hour_used(ocuped_arrival_hours, flight_arrival.hour, line) || 
            hour_used(ocuped_departure_hours, flight_departure.hour, line))
        {
            fclose(file);
            fprintf(stderr, "Sólo hay una llegada y una salida por hora a lo largo del día.\n");
            exit(EXIT_FAILURE);
        }
        ocuped_arrival_hours[line] = flight_arrival.hour;
        ocuped_departure_hours[line] = flight_departure.hour;
        /*Puedo utilizar directamente el tipo del vuelo ya que si se llegó a estas asignaciones es porque los
        tipos se corresponden de acuerdo a lo esperado.*/
        array[flight_arrival.hour - 1][arrival] = flight_arrival;
        array[flight_departure.hour - 1][departure] = flight_departure;
        ++line;
    }
    /*Por el mismo motivo de la segunda condición en la guarda del while y como a lo largo del día hay sólo una 
    salida y una llegada por hora, se debe verificar que el archivo contenga exactamente 24 líneas.*/
    if (line != HOURS)
    {
        fclose(file);
        fprintf(stderr, "El archivo debe contener exactamente %u líneas.\n", HOURS);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}
