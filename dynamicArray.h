#ifndef LANGTONSANT_DYNAMICARRAY_H
#define LANGTONSANT_DYNAMICARRAY_H
#endif //LANGTONSANT_DYNAMICARRAY_H

#include <stdlib.h>

/**
 * Dynamic Array Structure
 */
typedef struct {
    int *array;
    size_t used;
    size_t size;
} Array;

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
void arrayInit(Array *a, size_t initialSize);

/**
 * Initializes an Array. Every cell has the value 0.
 * @param a the array to initialize
 * @param initialSize the starting size
 */
void array2dInit(Array2D *a, size_t sizeX, size_t sizeY);

/**
 * Appends an element to the Array
 * @param a Array
 * @param element The element to be added to the array
 */
void arrayInsert(Array *a, int element);

/**
 * Appends an element to the Array
 * @param a Array
 * @param element The element to be added to the array
 */
void array2dInsert(Array2D *a, int element);

/**
 * Frees an Array
 * @param a Array to be freed
 */
void arrayFree(Array *a);

/**
 * Frees an Array
 * @param a Array to be freed
 */
void array2dFree(Array2D *a);