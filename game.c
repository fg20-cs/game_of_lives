#include "board.h"

const integ POPULATION_INITIAL = 500;


int main(int argc, char** argv){

    // Seting the SDL
    if (SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "Error: could not initialize SDL: %s\n", SDL_GetError());
        goto SDLInitializationError;
    }

    // Setting up a window
    SDL_WindowFlags flags = SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_MINIMIZED;
    SDL_Window * window = SDL_CreateWindow("Conway's game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, flags);
    if (window == NULL){
        fprintf(stderr, "Error: could not create a window: %s\n", SDL_GetError());
        goto WindowCreationError;
    }

    // Creating a renderer
    SDL_Renderer * renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC );
    if (renderer == NULL){
        fprintf( stderr, "error creating renderer: %s\n", SDL_GetError( ) );
        goto RendererCreationError;
    }


    // Initialize the board and the players view on it
    view play_view;
    int window_W, window_H;
    SDL_GL_GetDrawableSize(window, &window_W, &window_H);

    play_view.cellSize = 10;
    play_view.cellHeight = window_H/play_view.cellSize;
    play_view.cellWidth = window_W/play_view.cellSize;
    play_view.windowHeight = window_H;
    play_view.windowWidth = window_W;
    play_view.cellSpeed = 3;
    play_view.minPixelsSpeed = play_view.minPixelsSpeed * play_view.cellSize;

    const int BOARD_Height = play_view.windowHeight/4;
    const int BOARD_Width = play_view.windowWidth/4;
    board* cell_board = board_init(BOARD_Height, BOARD_Width, POPULATION_INITIAL);

    play_view.viewX = (BOARD_Width - play_view.cellWidth)/2;
    play_view.viewY = (BOARD_Height - play_view.cellHeight)/2;

    int living_cells = 0;
    SDL_Event e;
    integ last_update_time = 0;
    integ ticks_per_lifecycle = 1000;

    uint8_t quit = FALSE;
    uint8_t paused = FALSE;

    draw_board( cell_board, &play_view, renderer );

    // Game loop
    while (!quit){

        while ( SDL_PollEvent( &e ) ){
            if (e.type == SDL_QUIT)
                    quit = TRUE;
        }
        // Only update the board at the interval stored in ticks_per_lifecycle
        if (!((SDL_GetTicks() - last_update_time) < ticks_per_lifecycle) && !paused){
            living_cells = update_board(cell_board);
            last_update_time = SDL_GetTicks();
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if (SDL_RenderClear(renderer ))
            fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        draw_board(cell_board, &play_view, renderer);
    }

    //Cleaning up
    free(cell_board);

    SDL_DestroyRenderer(renderer);
    RendererCreationError:

    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(flags);
    WindowCreationError:

    SDL_Quit();
    SDLInitializationError:

    return EXIT_SUCCESS;
}