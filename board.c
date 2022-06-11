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

boolean change_cell_state(int x, int y, boolean state, board * b){
    if (!pos_in_board(x, y, b))
        return FALSE;
    int bitmask = cell_bitmask(x, y, b);
    if (state)
        return b->grid[(y*b->columns + x)/8] |= bitmask;

    return b->grid[(y*b->columns + x)/8] &= ~bitmask;
}

boolean cell_state(int x, int y, board * b){

    if (!pos_in_board(x, y, b))
        return FALSE;

    int bitmask = cell_bitmask(x, y, b);
    int cell_state = b->grid[(( y*b->columns + x )/8)];

    return ((cell_state & bitmask) != 0);
}

int living_neighbors(int x, int y, board * b){

    return cell_state(x - 1, y - 1, b) + cell_state(x    , y - 1, b) +
           cell_state(x + 1, y - 1, b) + cell_state(x - 1, y    , b) +
           cell_state(x + 1, y    , b) + cell_state(x - 1, y + 1, b) +
           cell_state(x    , y + 1, b) + cell_state(x + 1, y + 1, b);
}

boolean updated_cell_state(int x, int y, board* b){
    
    int living_neighbor_cells = living_neighbors(x, y, b);
    return (living_neighbor_cells == 3 || (cell_state(x, y, b) && (living_neighbor_cells == 2)));
}