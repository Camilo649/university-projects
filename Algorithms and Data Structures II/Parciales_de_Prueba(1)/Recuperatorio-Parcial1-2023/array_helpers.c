/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "wagon.h"

#define EXPECTED_WAGON_CODE_FORMAT " [%c] #%u %ukg "

//Tipo de datos auxiliar para guardar todos los números de vagón utilizados y hacer chequeos.
typedef unsigned int Combinations[MAX_SIZE];

/**
 * @brief Devuelve true si efectivamente un vagón tiene carga de tipo oatmeal.
 * @param[in] wp vagón de selección 'primary'
 * @param[in] ws vagón de selección 'secondary'
 */
static bool wagon_contain_oatmeal(Wagon wp, Wagon ws){

  return (wp.cargo == oatmeal && wp.weight != 0u) ||
         (ws.cargo == oatmeal && ws.weight !=0u);
}

/**
 * @brief Devuelve true si el número de vagón se encuentra en un rango factible.
 * @param[in] wagon_number número de vagón a chequear
 * @param[in] size cantidad total de vagones esperados
 */
static bool is_valid_wagon_number(unsigned int wagon_number, unsigned int size){

  return (wagon_number != 0) && (wagon_number <= size);
}

/**
 * @brief Devuelve true si 'wagon_number' no se encuentra en 'c'.
 * @param[in] c arreglo con los números ya utilizados
 * @param[in] wagon_number número de vagón a chequear
 * @param[in] size cantidad total de números de vagones en 'c'
 */
static bool not_is_used_wagon_number(Combinations c, unsigned int wagon_number, unsigned int size){
  bool used = true;
  unsigned int i = 0u;

  while (i<size && used)
  {
    used = (c[i] != wagon_number);
    ++i;
  }

  return used;
}

char * cargo_type_to_str(cargo_t cargo) {
  if (cargo == rice)
    return "rice";
  if (cargo == mushrooms)
    return "mushrooms";
  if (cargo == oatmeal)
    return "oatmeal";
  if (cargo == pepper)
    return "pepper";
  return "error";
}

static void
dump_cargo(Wagon w) {
    fprintf(stdout, "[%s cargo: %u kg of %s] ", 
                    w.section == primary ? "primary": "secondary",
                    w.weight, 
                    cargo_type_to_str(w.cargo));
}

void array_dump(Train t, unsigned int size) {
  for (unsigned int i = 0u; i < size; ++i) {
    Wagon wp = t[i][primary];
    Wagon ws = t[i][secondary];
    fprintf(stdout, "wagon %u: ", wp.number);
    dump_cargo(wp);
    dump_cargo(ws);
    if (i != size-1) {
      fprintf(stdout, "\n");
    }
  }
}

bool has_to_discard_wagons(Train t, unsigned int size) {
     bool discard = false;
     unsigned int i = 0u;
     unsigned int adjoining_wagons_whit_oatmeal = 0u;

    while (i < size && !discard)
    {
      /*Si hay un vagón que contiene oatmeal, suma aumena en uno la variable 'adjoining_wagons_whit_oatmeal'.*/
      if (wagon_contain_oatmeal(t[i][primary], t[i][secondary]))
      {
        ++adjoining_wagons_whit_oatmeal;
        /*Si se llegaron a res vagones consecutivos con carga de tipo oatmeal, discard se convierte en true y termina el programa.*/
        if (adjoining_wagons_whit_oatmeal == 3)
        {
          discard = true;
        }
      }
      /*Si no se alcanzaron 3 vagones consecutivos con la carga oatmeal, la variable 'adjoining_wagons_whit_oatmeal' vuelve a 0.*/
      else
      {
        adjoining_wagons_whit_oatmeal = 0u;
      }
      ++i;
    }

     return discard; 
}

// the wagon data should be saved on array
// the number of wagons should be stored on trainSize
void array_from_file(Train array, unsigned int * trainSize, const char *filepath) {
  FILE *file = NULL;
  char code;
  unsigned int size = 0u;
  unsigned int totalKg = 0u;
  int res = 0;
  unsigned int line = 0u;
  unsigned int actualKg = 0u;
  Combinations used_wagon_numbers;

  file = fopen(filepath, "r");
  if (file == NULL) 
  {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  res = fscanf(file, EXPECTED_WAGON_CODE_FORMAT, &code, &size, &totalKg);
  if (res != 3) {
    fclose(file);
    fprintf(stderr, "Invalid file.\n");
    exit(EXIT_FAILURE);
  }

  if (size > MAX_SIZE)
  {
    fclose(file);
    fprintf(stderr, "La cantidad máxima de vagones soportada es %u.\n", MAX_SIZE);
    exit(EXIT_FAILURE);
  }

  *trainSize = size;

  while (line < size) {
    if (feof(file))
  {
    fclose(file);
    fprintf(stderr, "La cantidad de vagones esperada (%u) no es acorde con la cantidad total de vagones.\n", size);
    exit(EXIT_FAILURE);
  }
    // Read wagon-number
    unsigned int wagon_number=0u;
    res = fscanf(file, " %u ", &wagon_number);
    if (res != 1 || !is_valid_wagon_number(wagon_number, size)) 
    {
      fclose(file);
      fprintf(stderr, "Error reading wagon-number at line %u.\n", line+2);
      exit(EXIT_FAILURE);
    }
    if (!not_is_used_wagon_number(used_wagon_numbers, wagon_number, line))
    {
      fclose(file);
      fprintf(stderr, "Estás repitiendo el número del vagón en la línea %u.\n", line+2);
      exit(EXIT_FAILURE);
    }
    used_wagon_numbers[line] = wagon_number;

    // Read wagon's primary cargo
    Wagon wagon_primary = wagon_from_file(wagon_number, primary, file);
    // Read wagon's seconday cargo
    Wagon wagon_secondary = wagon_from_file(wagon_number, secondary, file);
    // Store data in array
    array[wagon_number - 1][primary] = wagon_primary;
    array[wagon_number - 1][secondary] = wagon_secondary;
    actualKg += wagon_primary.weight + wagon_secondary.weight;
    if (actualKg > totalKg)
    {
      fclose(file);
      fprintf(stderr, "La suma del peso de los vagones es mayor a la cantidad indicada (%u).\n"
                      "Cantidad superada en la línea %u.\n", totalKg, line+2);
      exit(EXIT_FAILURE);
    }
    ++line;
  }
  if (!feof(file))
  {
    fclose(file);
    fprintf(stderr, "No se han leído todos los vagones cargados, revisar estar ingresando correctamente el número de vagones.\n");
    exit(EXIT_FAILURE);
  }
  if (actualKg < totalKg)
  {
    fclose(file);
    fprintf(stderr, "Se indicó un peso de %u, sin embargo el peso real del tren es de %u.\n", totalKg, actualKg);
    exit(EXIT_FAILURE);
  }

  fclose(file);
}