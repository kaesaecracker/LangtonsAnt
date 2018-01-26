#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qdbmp.h"
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

// BMP
#define PALLETTE_WHITE 255
#define PALLETTE_BLACK 0
#define PALLETTE_ANT 100
#define BMP_SCALE 5

typedef struct {
    int x, y, orientation;
} Ant;

Array2D field;
Ant ant;
int assEnabled = FALSE;
int bmpEnabled = FALSE;
int stdoutEnabled = FALSE;
unsigned long maxSteps = 0;
unsigned long steps = 0;

int drawFieldToBmp() {
    // get file name
    char fileName[60] = "";
    snprintf(fileName, sizeof fileName, "./images/%lu.bmp", steps);
    //printf("Printing to file %s...\n", fileName);

    // create bitmap
    BMP* bmp = BMP_Create(field.sizeX * BMP_SCALE, field.sizeY * BMP_SCALE, 8);
    BMP_SetPaletteColor(bmp, PALLETTE_BLACK, 0, 0, 0);
    BMP_SetPaletteColor(bmp, PALLETTE_WHITE, 255, 255, 255);
    BMP_SetPaletteColor(bmp, PALLETTE_ANT, 255, 0, 0);

    // set values of bitmap
    for (unsigned int y = 0; y < (unsigned int) field.sizeY; y++) {
        for (unsigned int x = 0; x < (unsigned int) field.sizeX; x++) {
            for (unsigned int subpixel_x = 0; subpixel_x < BMP_SCALE; subpixel_x++) {
                for (unsigned int subpixel_y = 0; subpixel_y < BMP_SCALE; subpixel_y++) {
                    BMP_SetPixelIndex(bmp, x * BMP_SCALE + subpixel_x, y * BMP_SCALE + subpixel_y,
                                      (unsigned char) (field.array[x][y] == BLACK ? PALLETTE_BLACK : PALLETTE_WHITE));
                }
            }
        }
    }

    BMP_CHECK_ERROR(stdout, -1);

    // write to file
    BMP_WriteFile(bmp, fileName);
    BMP_CHECK_ERROR(stdout, -1);

    // free resources
    BMP_Free(bmp);
}

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

    steps++;
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
    if (bmpEnabled) printf("; BMP print enabled");
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

int queryIsYes(char *msg, int defaultValue) {
    printf("%s", msg);
    if (defaultValue == TRUE) {
        printf(" (Y/n) : ");
    } else {
        printf(" (y/N) : ");
    }

    char input;
    fflush(stdin);
    scanf(" %c", &input);
    printf("\n");

    if (defaultValue == TRUE) {
        return ((input != 'n') && (input != 'N'));
    } else {
        return ((input == 'y') || (input == 'Y'));
    }
}

int main() {
    // Input field
    int x = 0, y = 0;
    while (x < 1 || y < 1) {
        printf("Groesse des Feldes in X-Richtung: ");
        scanf("%d", &x);
        printf("Groesse des Feldes in Y-Richtung: ");
        scanf("%d", &y);
    }

    array2dInit(&field, x, y);

    // input ant
    x = -1, y = -1;
    while (x < 0 || y < 0 || x > field.sizeX || y > field.sizeY) {
        printf("X-Position der Ameise: ");
        scanf("%d", &x);
        printf("Y-Position der Ameise: ");
        scanf("%d", &y);
    }

    ant = (Ant){
            .x = x,
            .y = y,
            .orientation = NORTH
    };

    // settings
    assEnabled = queryIsYes("Do not want to enable ASS (Anti Stuck System)?", TRUE);
    bmpEnabled = queryIsYes("Do you want to create an image for every step in ./images/?", TRUE);
    stdoutEnabled = queryIsYes("Do you want to print to console?", FALSE);

    // if no output -> how many generations?
    if (!stdoutEnabled) {
        printf("How many steps do you want to do? (0=infinite): ");
        fflush(stdin);
        scanf("%lu", &maxSteps);
    }

    // print ffmpeg command
    if (bmpEnabled) {
        int pixelsX = (int) (BMP_SCALE * field.sizeX), pixelsY = (int) (BMP_SCALE * field.sizeY);
        printf("ffmpeg.exe -r 20 -f image2 -s %dx%d -i ./images/%s.bmp -vcodec libx264 -pix_fmt yuv420p ./out.mp4\n",
               pixelsX, pixelsY, "%d");
    }


    int exit = FALSE;
    printf("Starting loop...\n");
    while (!exit) {
        if (stdoutEnabled) printField();
        if (bmpEnabled) drawFieldToBmp();

        if (stdoutEnabled) {
            exit = queryIsYes("Do you want to stop?", FALSE);
        } else {
            if (steps % 100 == 0){
                printf("Reached step %lu\n", steps);
                fflush(stdout);
            }

            exit = (maxSteps != 0) && (steps >= maxSteps);
        }

        langtonsAnt();
    }

    return 0;
}