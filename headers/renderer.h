#pragma once
#include "scene.h"
#include <SDL2/SDL.h>

class Renderer{
    public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Canvas  canvas;
    Scene scene;
    bool is_running;
    bool is_rendering;
    bool shift_down;
    bool ctrl_down;
    bool with_thread;
    int movement_speed;

    Renderer(Scene& scene, Canvas& canvas);
    Renderer(Scene& scene, int width, int height);

    void handleInput(SDL_Event& event);
    void renderFrame();
    void render();
    int startWindow(int width, int height);
    void start();
};