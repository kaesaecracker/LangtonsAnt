#include "dynamicArray.h"

/*                                          ARRAY                                                                       */
void arrayInit(Array *a, size_t initialSize) {
    a->array = (int *) malloc(initialSize * sizeof(int));
    a->used = 0;
    a->size = initialSize;
}

void arrayInsert(Array *a, int element) {
    // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (int *) realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void arrayFree(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

void arraySetValueAt(Array *a, int index, int newValue) {
    a->array[index] = newValue;
}

/*                                    ARRAY2D                                                                           */
void array2dInit(Array2D *a, size_t sizeX, size_t sizeY) {
    *a = (Array2D){
            .sizeY = sizeY,
            .sizeX = sizeX,
            .array = malloc(sizeX * sizeof(int *))
    };

    for (int x = 0; x < sizeX; x++) {
        a->array[x] = malloc(sizeY * sizeof(int));

        for (int y = 0; y < sizeY; y++) {
            a->array[x][y] = 0;
        }
    }
}

