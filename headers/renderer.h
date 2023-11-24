#pragma once
#include "scene.h"
#include <SDL2/SDL.h>

class Renderer{
    public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Canvas canvas;
    Scene scene;
    bool is_running;
    bool is_rendering;

    Renderer(Scene& scene, Canvas& canvas);

    void handleInput(SDL_Event& event);
    void renderFrame();
    void render();
    int startWindow(int width, int height);
    void start();
};