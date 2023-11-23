#include "../headers/renderer.h"
#include <iostream>

Renderer::Renderer(Scene& scene, Canvas& canvas){
    int width = canvas.columns;
    int height = canvas.rows;
    this->scene = scene;
    this->canvas = canvas;
    if(startWindow(width, height) == 0){
        renderFrame();
        render();
    }
}

int Renderer::startWindow(int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return 1;
    }

    this->window = SDL_CreateWindow("Color Matrix", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    return 0;
}

void Renderer::handleInput(SDL_Event& event){
    bool update = false;
    bool resize = false;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            is_running = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = canvas.columns - event.button.x;
                int mouseY = canvas.rows - event.button.y;

                cout << "Mouse clicked at (x = " << mouseX << ", y = " << mouseY << ")" << endl;
                optional<LitPoint> intersect = scene.get_closest_colision(mouseX, mouseY);

                if(intersect.has_value() && intersect.value().t > 0){
                    LitPoint at = intersect.value();
                    cout << "Intersection at (x = " << at.x << ", y = " << at.y << ", z = " << at.z << ")" << endl;
                    scene.camera.lookAt(at, Point(scene.camera.origin + Vector(0, 1, 0)));
                    update = true;
                    is_rendering = true;
                }
            }  
        }
        else if (event.type == SDL_KEYDOWN) {
            cout << "Tecla pressionada: ";
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    cout << "w" << endl;
                    scene.camera.origin = scene.camera.origin + scene.camera.k;
                    break;
                case SDLK_a:
                    cout << "a" << endl;
                    scene.camera.origin = scene.camera.origin + scene.camera.i;
                    break;
                case SDLK_d:
                    cout << "d" << endl;
                    scene.camera.origin = scene.camera.origin - scene.camera.i;
                    break;
                case SDLK_s:
                    cout << "s" << endl;
                    scene.camera.origin = scene.camera.origin - scene.camera.k;
                    break;
                case SDLK_SPACE:
                    cout << "SPACE" << endl;
                    scene.camera.origin = scene.camera.origin + scene.camera.j;
                    break;
                case SDLK_c:
                    cout << "c" << endl;
                    scene.camera.origin = scene.camera.origin - scene.camera.j;
                    break;
            }
            is_rendering = true;
            update = true;
        }
        else if (event.type == SDL_KEYUP) {
            // Check for the key you are interested in
            cout << "Tecla pressionada: ";
            switch (event.key.keysym.sym) {
                case SDLK_i:
                    cout << "i" << endl;
                    scene.camera.d += 1.0;
                    cout << "Current d: " << scene.camera.d << endl;
                    break;
                case SDLK_o:
                    cout << "o" << endl;
                    scene.camera.d = max(1.0, scene.camera.d - 1.0);
                    cout << "Current d: " << scene.camera.d << endl;
                    break;
                case SDLK_EQUALS:
                // Expand the screen when the '=' key is pressed
                    cout << "=" << endl;
                    canvas.resize(canvas.columns + 50, canvas.rows + 50);
                    scene.camera = Camera(
                        scene.camera.origin, 
                        scene.camera.i, 
                        scene.camera.j, 
                        scene.camera.k, 
                        scene.camera.width,
                        scene.camera.height, 
                        canvas.rows, 
                        canvas.columns,
                        scene.camera.d
                    );
                    cout << "Current resolution: (" << canvas.columns << ", " << canvas.rows << ")" << endl;
                    resize = true;
                    break;
                case SDLK_MINUS:
                    cout << "-" << endl;
                    // Reduce the screen when the '-' key is pressed
                    canvas.resize(max(50, canvas.columns - 50), max(50, canvas.rows - 50));
                    scene.camera = Camera(
                        scene.camera.origin, 
                        scene.camera.i, 
                        scene.camera.j, 
                        scene.camera.k, 
                        scene.camera.width,
                        scene.camera.height, 
                        canvas.rows, 
                        canvas.columns,
                        scene.camera.d
                    );
                    cout << "Current resolution: (" << canvas.columns << ", " << canvas.rows << ")" << endl;
                    resize = true;
                    break;
                // Add more cases for other keys as needed
            }
            is_rendering = true;
            update = true;
        }
    }
    if(update){
        scene.paint(canvas);
        is_rendering = false;
    }
    if(resize){
        SDL_SetWindowSize(window, canvas.columns, canvas.rows);

        // Recreate the SDL renderer
        SDL_DestroyRenderer(renderer);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            // Handle renderer creation failure
            return;
        }
    }
}
void Renderer::renderFrame(){
    SDL_RenderClear(renderer);

    for (int y = 0; y < canvas.rows; ++y) {
        for (int x = 0; x < canvas.columns; ++x) {
            Color color = canvas.matrix[y][canvas.columns-x-1];  

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    SDL_RenderPresent(renderer);
}

void Renderer::render(){

    SDL_Event event;
    is_rendering = false;

    while (is_running) {
        if(!is_rendering){
            //cout << "Handling input. is_rendering:" << is_rendering << endl;
            handleInput(event);
            renderFrame();
        }
        SDL_Delay(32);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}