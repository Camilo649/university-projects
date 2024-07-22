/*
@file wagon.c
@brief Implements wagon structure and methods
*/
#include <stdlib.h>
#include "wagon.h"

static const int AMOUNT_OF_WAGON_VARS = 2;

Wagon wagon_from_file(unsigned int wagon_num, section_t section, FILE* file)
{
  Wagon wagon;
  char cargoType;
  int res = 0;

  wagon.number = wagon_num;
  wagon.section = section;

  res = fscanf(file, EXPECTED_WAGON_LINE_FORMAT, &cargoType, &wagon.weight);
  if (res != AMOUNT_OF_WAGON_VARS)
  {
    fclose(file);
    fprintf(stderr, "Invalid file.\n");
    exit(EXIT_FAILURE);
  }

  if (cargoType == 'r') {
    wagon.cargo = rice;
  } else if (cargoType == 'm') {
    wagon.cargo = mushrooms;
  } else if (cargoType == 'o') {
    wagon.cargo = oatmeal;
  } else if (cargoType == 'p') {
    wagon.cargo = pepper;
  } else {
    fprintf(stderr, "Invalid cargo type at wagon[%u]\n", wagon_num);
    exit(EXIT_FAILURE);

  }

  return wagon;
}
