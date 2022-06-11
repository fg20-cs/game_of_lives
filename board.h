#ifndef BOARD_H
#define BOARD_H

#define FALSE 0
#define TRUE 1

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

#include "SDL2/SDL.h"

//Living cells
#define LIVING_CELL_R 255
#define LIVING_CELL_G 255
#define LIVING_CELL_B 255

//Dead cells
#define DEAD_CELL_R 15
#define DEAD_CELL_G 15
#define DEAD_CELL_B 15

typedef Uint8 boolean;
typedef Uint32 integ;

typedef struct{
    int rows, columns;
    boolean grid[0];
} board;

typedef struct{

    int viewX,
        viewY,
        cellSize,
        cellHeight,
        cellWidth,
        windowHeight,
        windowWidth,
        cellSpeed,
        minPixelsSpeed;

}view;

int board_byte_size(int rows, int columns);
boolean pos_in_board(int x, int y, board * b);
int cell_bitmask( int x, int y, board *b );


#endif