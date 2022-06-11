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

    
    //Cleaning up
    

    SDL_DestroyRenderer(renderer);
    RendererCreationError:

    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(flags);
    WindowCreationError:

    SDL_Quit();
    SDLInitializationError:
    

    return EXIT_SUCCESS;
}

