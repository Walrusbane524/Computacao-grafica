#include <math.h>
#include <optional>
#include <SDL2/SDL.h>
#include <iostream>
#include <limits>
#include "headers/camera.h"
#include "headers/canvas.h"
#include "headers/color.h"
#include "headers/object.h"
#include "headers/point.h"
#include "headers/ray.h"
#include "headers/vec.h"
#include "headers/sphere.h"

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 3;

    Camera camera = Camera(Point(0, 0, 20), 1, -1, 1, -1, n_l, n_c, -d);
    Canvas canvas = Canvas(n_l, n_c);
    Sphere objetos[3];
    objetos[0] = Sphere(Point(0, -15, -100), 20, Color(255, 255, 255));
    objetos[1] = Sphere(Point(0, 10, -100), 15, Color(255, 255, 255));
    objetos[2] = Sphere(Point(0, 30, -100), 10, Color(255, 255, 255));
    Color background = Color(100, 100, 100);

    for(int l = 0; l < camera.n_l; l++){
        double y_l = camera.j_ymax - (camera.delta_y/2.0) - (l*camera.delta_y);
        for(int c = 0; c < camera.n_c; c++){
            double x_c = camera.j_xmin + (camera.delta_x/2.0) + (c*camera.delta_x);
            Point p_j = Point(x_c, y_l, camera.origin.z -d);
            Ray ray = Ray(camera.origin, p_j);
            Color cor_atual = background;
            double smallest_root = numeric_limits<double>::infinity();
            for(Sphere s : objetos){
                optional<double> intersect = s.colide(ray);
                if (intersect.has_value()){
                    double root = intersect.value();
                    if(root < smallest_root){
                        root = smallest_root;
                        cor_atual = s.color;
                    }
                }
            }
            canvas.matrix[l][c] = cor_atual;
        }
    }

    int width = n_l;
    int height = n_c;

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

        for (int y = 0; y < canvas.rows; ++y) {
            for (int x = 0; x < canvas.columns; ++x) {
                Color color = canvas.matrix[y][x];  

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