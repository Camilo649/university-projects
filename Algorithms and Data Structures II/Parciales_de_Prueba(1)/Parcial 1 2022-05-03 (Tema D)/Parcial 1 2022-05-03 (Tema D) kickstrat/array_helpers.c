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
static const int DECIMAS = 1; //Cantidad de números depués de la coma en la macro 'COMPENSATION_PER_MINUTE'.

#define INTERGER_COMPENSATION COMPENSATION_PER_MINUTE * 10 * DECIMAS

struct type_hour
{
	flight_t type;
	unsigned int hour;
};

typedef struct type_hour Combinations[HOURS];

/**
 * @brief returns true when reach last line in flight file
 * @return True when is the last line of the file, False otherwise
 */
static bool is_last_line(unsigned int hour, unsigned int type)
{
	return hour == HOURS - 1u && type == TYPE - 1u;
}

static void invalid_file(FILE *file){
	fclose(file);
	fprintf(stderr, "Invalid file.\n");
	exit(EXIT_FAILURE);
}

static unsigned int calculate_cost(flight_t type, unsigned int delay, unsigned int passengers){

	return (delay - (type == 0? MAX_LM_DELAY_ALLOWED : MAX_LAYOVER_DELAY_ALLOWED)) * 
		   INTERGER_COMPENSATION * passengers;
}

static bool is_valid_hour(unsigned int hour){

    return (hour != 0u) && (hour <= HOURS);
}

static bool combination_exists(Combinations c, unsigned int hour, unsigned int lines){
	bool exist=false;
	unsigned int line = 0u;

	while (line < lines && !exist)
	{
		exist = (c[line].hour == hour);
		++line;
	}
	
	return exist;
}

void array_dump(DelayTable a)
{
	for (unsigned int type = 0u; type < TYPE; ++type)
	{
		for (unsigned int hour = 0u; hour < HOURS; ++hour)
		{
			Flight f = a[type][hour];
			fprintf(stdout, "%c: %s flight with %u passengers arrived at %u:00, with %u delay",
					f.code,
					f.type == 0 ? "last_mile" : "layover",
					f.passengers_amount,
					f.hour - 1,
					f.delay);
			if (!is_last_line(hour, type))
			{
				fprintf(stdout, "\n");
			}
		}
	}
}

unsigned int compensation_cost (DelayTable a, unsigned int h) {
	unsigned int cost=0u;
	
	for (unsigned int type = 0u; type < TYPE; ++type)
	{
		for (unsigned int hour = 0u; hour < h; ++hour)
		{
			if (a[type][hour].delay > (type == 0? MAX_LM_DELAY_ALLOWED : MAX_LAYOVER_DELAY_ALLOWED))
			{
				cost = cost + calculate_cost(type, a[type][hour].delay, a[type][hour].passengers_amount);
			}
		}
	}

	return cost / (10 * DECIMAS); //La divisón por 10 deriva de pasar la compensación a un valor entero.
}

void array_from_file(DelayTable array, const char *filepath)
{
	FILE *file = NULL;
	char code;
	int line = 0;
	int res = 0;
	Combinations used_last_mile_combinations;
	Combinations used_layover_combinations;

	file = fopen(filepath, "r");
	if (file == NULL)
	{
		fprintf(stderr, "File does not exist.\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(file))
	{
		Flight last_mile_info = flight_from_file(file);
		Flight layover_info = flight_from_file(file);
		/*Esto lo puedo hacer pues la primera terna de datos corresponden al tipo last_mile*/
		last_mile_info.type = last_mile;
		/*Esto lo puedo hacer pues la segunda terna de datos corresponden al tipo layover*/
		layover_info.type = layover;
		if (!is_valid_hour(last_mile_info.hour) || !is_valid_hour(layover_info.hour) ||
			combination_exists(used_last_mile_combinations, last_mile_info.hour, line) || 
			combination_exists(used_layover_combinations, layover_info.hour, line))
		{
			invalid_file(file);
		}
		used_last_mile_combinations[line].type = last_mile_info.type;
		used_last_mile_combinations[line].hour = last_mile_info.hour;
		used_layover_combinations[line].type = layover_info.type;
		used_layover_combinations[line].hour = layover_info.hour;
		res = fscanf(file, EXPECTED_FLIGHT_CODE_FORMAT, &code);
		if (res != AMOUNT_OF_CODE_VAR)
		{
			invalid_file(file);
		}

		last_mile_info.code = code;
		layover_info.code = code;
		array[last_mile][last_mile_info.hour - 1] = last_mile_info;
		array[layover][layover_info.hour - 1] = layover_info;
		++line;
	}
	/*Como a lo largo del día hay una llegada para cada tipo por hora, solo voy a leer 24 lines en total.
	  Ni más ni menos.*/
	if (line != HOURS)
	{
		invalid_file(file);
	}
	
	fclose(file);
}
