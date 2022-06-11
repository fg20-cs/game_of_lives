#include "board.h"

#define MIN_CELL_SIZE 2 
#define MAX_CELL_SIZE 30

int board_byte_size(int rows, int columns){

    int size = sizeof(board) + (rows * columns)/8;
    if(rows * columns % 8)
        size +=1;
    
    return size;
}

boolean pos_in_board(int x, int y, board * b){
    boolean pos = (x >= 0 && y >= 0 && x < b->columns && y < b->rows);
    return pos;
}


int cell_bitmask( int x, int y, board *b ){
    int birmask =  (int) 2^((y*b->columns + x) % 8);
    return birmask;
}

