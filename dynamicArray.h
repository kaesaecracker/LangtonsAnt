#ifndef LANGTONSANT_DYNAMICARRAY_H
#define LANGTONSANT_DYNAMICARRAY_H
#endif //LANGTONSANT_DYNAMICARRAY_H

#include <stdlib.h>

/**
 * Dynamic Array of Array structure
 */
typedef struct {
    int **array;
    size_t sizeX, sizeY;
} Array2D;

/**
 * Initializes an Array. Every cell has the value 0.
 * @param a the array to initialize
 * @param initialSize the starting size
 */
void array2dInit(Array2D *a, size_t sizeX, size_t sizeY);