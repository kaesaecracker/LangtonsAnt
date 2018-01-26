#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"

// booleans
#define TRUE 1
#define FALSE 0

// tile colors
#define BLACK 1
#define WHITE 0

// ant orientations
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

typedef struct {
    int x, y, orientation;
} Ant;

Array2D field;
Ant ant;
int assEnabled = FALSE;
unsigned long steps = 0;

void ass() {
    if (ant.x == 0) { // left
        if (ant.y == 0) { // top
            ant.x++;
            ant.y++;
        } else if (ant.y == field.sizeY - 1) { // bottom
            ant.x++;
            ant.y--;
        }
    } else if (ant.x == field.sizeX - 1) { // right
        if (ant.y == 0) { // top
            ant.x--;
            ant.y++;
        } else if (ant.y == field.sizeY - 1) { // bottom
            ant.x--;
            ant.y--;
        }
    }
}

void changeOrientation() {
    if (field.array[ant.x][ant.y] == WHITE) {
        ant.orientation = (ant.orientation + 1) % 4;
    } else {
        ant.orientation = (ant.orientation - 1) % 4;
        ant.orientation = (ant.orientation >= 0) ? ant.orientation : (4 + ant.orientation);
    }

}

void moveAnt() {
    switch (ant.orientation) {
        case NORTH:
            ant.y -= 1;
            break;
        case EAST:
            ant.x += 1;
            break;
        case SOUTH:
            ant.y += 1;
            break;
        case WEST:
            ant.x -= 1;
            break;

        default:
            printf("The ant entered the 3rd dimension o_O\n");
    }
}

void keepInBounds() {
    if (ant.x < 0) ant.x = 0;
    if (ant.x >= field.sizeX) ant.x = (int) field.sizeX - 1;
    if (ant.y < 0) ant.y = 0;
    if (ant.y >= field.sizeY) ant.y = (int) field.sizeY - 1;
}

void langtonsAnt() {
    changeOrientation();
    field.array[ant.x][ant.y] = (field.array[ant.x][ant.y] == WHITE) ? BLACK : WHITE;
    moveAnt();
    if (assEnabled) ass();
    keepInBounds();
}

void printAnt() {
    switch (ant.orientation) {
        case NORTH:
            printf("N");
            break;
        case EAST:
            printf("E");
            break;
        case SOUTH:
            printf("S");
            break;
        case WEST:
            printf("W");
            break;

        default:
            printf('A');
            break;
    }
}

void printField() {
    printf("Step %lu: X=%d Y=%d", steps, ant.x, ant.y);
    if (assEnabled) printf("; ASS enabled");
    printf("; Field: \n");

    for (int y = 0; y < field.sizeY; y++) {
        for (int x = 0; x < field.sizeX; x++) {
            if (ant.x == x && ant.y == y) {
                printAnt();
                continue;
            }

            if (field.array[x][y] == WHITE) {
                printf("░");
            } else {
                printf("▓");
            }
        }

        printf("\n");
    }
}

int main() {
    // Feld initialisieren
    int x = 0, y = 0;
    while (x < 1 || y < 1) {
        printf("Groesse des Feldes in X-Richtung: ");
        scanf("%d", &x);
        printf("Groesse des Feldes in Y-Richtung: ");
        scanf("%d", &y);
        array2dInit(&field, x, y);
    }

    // Ameise setzen
    x = -1, y = -1;
    while (x < 0 || y < 0 || x > field.sizeX || y > field.sizeY) {
        printf("X-Position der Ameise: ");
        scanf("%d", &x);
        printf("Y-Position der Ameise: ");
        scanf("%d", &y);
    }

    // ASS
    printf("Do not want to enable ASS (Anti Stuck System)? (Y/n): ");
    char input;
    fflush(stdin);
    scanf(" %c", &input);
    assEnabled = (input != 'n') && (input != 'N');

    Ant a = {
            .x = x,
            .y = y,
            .orientation = NORTH
    };
    ant = a;

    printf("Starting loop...\n");
    int exit = FALSE;
    while (!exit) {
        system("clear");
        printField();

        printf("Press enter to generate the next generation or type e to exit...");
        fflush(stdin);
        char input = getchar();
        printf("\n");
        if (input == 'e') {
            exit = TRUE;
        }

        langtonsAnt();
    }

    return 0;
}