#include <optional>
#include <SDL2/SDL.h>

#include "../headers/canvas.h"

Canvas::Canvas(){
    rows = 0;
    columns = 0;
    matrix = nullptr;
}

Canvas::Canvas(int n_l, int n_c){
    rows = n_l;
    columns = n_c;
    matrix = new Color*[n_l];
    for (int i = 0; i < n_l; i++)
        matrix[i] = new Color[n_c];
}

Canvas::~Canvas() {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

int Canvas::render(){
    int width = columns;
    int height = rows;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Color Matrix", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < columns; ++x) {
                Color color = matrix[y][columns-x-1];  

                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
