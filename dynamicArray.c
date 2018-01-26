#include "dynamicArray.h"

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

