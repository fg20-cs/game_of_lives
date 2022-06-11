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

board * board_init(int rows, int columns, int living_cell_num){

    board* board1 = (board * )calloc(1, board_byte_size(rows, columns));
    board1->rows = rows;
    board1->columns = columns;

    // Populate the board
    integ randomX, randomY;
    int bitmask;
    for (int i = 0; i < living_cell_num; i++){

        randomX = random()% columns;
        randomY = random()% rows;
        if (cell_state( randomX, randomY, board1 ) ){i--; continue;}
        change_cell_state( randomX, randomY, TRUE, board1 );
    }
    return board1;
}

int update_board(board * b){

    int living_cells_count = 0;
    board* temp =(board *)malloc(board_byte_size(b->rows, b->columns));
    if(temp == NULL){
        fprintf(stderr, "Failed to intialize board!\n");
        exit(1);
    }

    temp->rows = b->rows;
    temp->columns = b->columns;
    for (int y = 0; y < b->rows; y++){
        for (int x = 0; x < b->columns; x++){
            if ( change_cell_state( x, y, updated_cell_state(x, y, b), temp))
                living_cells_count++;    
        }
    }
    memcpy(b, temp, board_byte_size(b->rows, b->columns));
    free(temp);

    return living_cells_count;
}
