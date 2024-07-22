/*
  @file bakery_product.c
  @brief Implements bakery product structure and methods
*/
#include <stdlib.h>
#include "bakery_product.h"

static const int AMOUNT_OF_PRODUCT_VARS = 7;

BakeryProduct bakery_product_from_file(FILE *file)
{
    BakeryProduct product;
    int res = 0;

    res = fscanf(file, EXPECTED_PRODUCT_FILE_FORMAT, &product.sale_value,
                 &product.flour_cant, &product.flour_price,
                 &product.butter_cant, &product.butter_price,
                 &product.yeast_cant, &product.yeast_price);
    if (res != AMOUNT_OF_PRODUCT_VARS)
    {
        fprintf(stderr, "Invalid file.\n");
        exit(EXIT_FAILURE);
    }

    return product;
}
