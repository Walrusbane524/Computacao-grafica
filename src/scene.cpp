#include "../headers/scene.h"
#include <iostream>
#include <chrono>

using namespace std;

Scene::Scene(){
    this->ambient = Vec(0.2, 0.2, 0.2);
}

Scene::Scene(Camera camera, Color background){
    this->camera = camera;
    this->background = background;
    this->ambient = Vec(0.2, 0.2, 0.2);
}

Scene::Scene(Camera camera, Color background, Vec ambient){
    this->camera = camera;
    this->background = background;
    this->ambient = ambient;
}

Scene::Scene(Camera camera, Color background, vector<Object*> objects, vector<Light*> lights){
    this->camera = camera;
    this->background = background;
    this->objects = objects;
    this->lights = lights;
    this->ambient = Vec(0.2, 0.2, 0.2);
}

Scene::Scene(Camera camera, Color background, vector<Object*> objects, vector<Light*> lights, Vec ambient){
    this->camera = camera;
    this->background = background;
    this->objects = objects;
    this->lights = lights;
    this->ambient = ambient;
}

void Scene::addObject(Object* object){
    this->objects.push_back(object);
}

void Scene::addLight(Light* light){
    this->lights.push_back(light);
}

optional<LitPoint> Scene::get_closest_colision(int frame_x, int frame_y){
    int l = camera.n_l - frame_y;
    int c = frame_x;

    Vector diff_y = (camera.j * (camera.delta_y/2)) + ((camera.j * camera.delta_y) * l);
    Vector diff_x = (camera.i * (camera.delta_x/2)) + ((camera.i * camera.delta_x) * c);
    
    Point upper_left = camera.origin - (camera.i * camera.width/2) + (camera.j * camera.height/2) + (camera.k * camera.d);
    Point p_j = upper_left + diff_x - diff_y;
    Ray ray = Ray(camera.origin, p_j);

    double smallest_root = numeric_limits<double>::infinity();
    LitPoint closest_point;

    for(Object* s : objects){

        optional<LitPoint> intersect = s->colide(ray);
        
        if (intersect.has_value() && intersect.value().t > 0){
            double t = intersect.value().t;

            if(t < smallest_root){
                smallest_root = t;
                closest_point = intersect.value();
            }
        }
    }

    if(smallest_root < numeric_limits<double>::infinity()) return closest_point;
    return nullopt;
}

void Scene::paint(Canvas& canvas){
    
    auto start_time = chrono::high_resolution_clock::now();

    cout << "Rendering..." << endl;

    Point upper_left = camera.origin - (camera.i * camera.width/2) + (camera.j * camera.height/2) + (camera.k * camera.d);

    //cout << "Upper_left: " << upper_left.x << " " << upper_left.y << " " << upper_left.z << endl ;

    for(int l = 0; l < camera.n_l; l++){

        Vector diff_y = (camera.j * (camera.delta_y/2)) + ((camera.j * camera.delta_y) * l);
        
        for(int c = 0; c < camera.n_c; c++){

            Vector diff_x = (camera.i * (camera.delta_x/2)) + ((camera.i * camera.delta_x) * c);

            Point p_j = upper_left + diff_x - diff_y;

            //cout << "p_j: " << p_j.x << " " << p_j.y << " " << p_j.z << endl ;

            Ray ray = Ray(camera.origin, p_j);
            Color cor_atual = background;
            double smallest_root = numeric_limits<double>::infinity();
            LitPoint closest_point;
            bool intersected = false;

            for(long unsigned int i = 0; i < objects.size(); i++){

                optional<LitPoint> intersect = objects[i]->colide(ray);
                
                if (intersect.has_value() && intersect.value().t > 0){
                    LitPoint p = intersect.value();

                    if(p.t < smallest_root){
                        smallest_root = p.t;
                        closest_point = p;
                        intersected = true;
                    }
                }
            }
            if(intersected){

                Vec ambient_intensity = this->ambient * closest_point.material.ambient;
                Vec color_intensity = ambient_intensity;

                for(Light* light : lights){
                    Vec diffuse_specular = light->get_diffuse_and_specular(closest_point, this->objects, ray);
                    color_intensity = color_intensity + diffuse_specular;
                }

                if(color_intensity.x > 1) color_intensity.x = 1;
                if(color_intensity.y > 1) color_intensity.y = 1;
                if(color_intensity.z > 1) color_intensity.z = 1;  

                cor_atual = color_intensity * closest_point.color;
            }
            canvas.matrix[l][c] = cor_atual;
        }
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
    cout << "Done!" << endl;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds" << endl;
    is_rendering = false;
}

void Scene::handleInput(SDL_Event& event, Canvas& canvas){

    bool update = false;
    bool resize = false;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            is_running = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = canvas.columns - event.button.x;
                int mouseY = canvas.rows - event.button.y;

                cout << "Mouse clicked at (" << mouseX << ", " << mouseY << ")" << endl;
                optional<LitPoint> intersect = get_closest_colision(mouseX, mouseY);

                if(intersect.has_value() && intersect.value().t > 0){
                    LitPoint at = intersect.value();
                    cout << "Intersection at (" << at.x << ", " << at.y << ", " << at.z << ")" << endl;
                    camera.lookAt(at, Point(camera.origin + Vec(0, 1, 0)));
                    update = true;
                    is_rendering = true;
                }
            }  
        }
        else if (event.type == SDL_KEYDOWN) {
            // Check for the key you are interested in
            cout << "Tecla pressionada: ";
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    cout << "w" << endl;
                    camera.origin = camera.origin + camera.k;
                    break;
                case SDLK_a:
                    cout << "a" << endl;
                    camera.origin = camera.origin + camera.i;
                    break;
                case SDLK_d:
                    cout << "d" << endl;
                    camera.origin = camera.origin - camera.i;
                    break;
                case SDLK_s:
                    cout << "s" << endl;
                    camera.origin = camera.origin - camera.k;
                    break;
                case SDLK_SPACE:
                    cout << "SPACE" << endl;
                    camera.origin = camera.origin + camera.j;
                    break;
                
                case SDLK_c:
                    cout << "c" << endl;
                    camera.origin = camera.origin - camera.j;
                    break;
                case SDLK_EQUALS:
                // Expand the screen when the '=' key is pressed
                    canvas.columns += 10;
                    camera.n_c = canvas.columns;
                    canvas.rows += 10;
                    camera.n_l = canvas.rows;
                    resize = true;
                    break;
                case SDLK_MINUS:
                    // Reduce the screen when the '-' key is pressed
                    canvas.columns = max(10, canvas.columns - 10);
                    camera.n_c = canvas.columns;
                    canvas.rows = max(10, canvas.rows - 10);
                    camera.n_l = canvas.rows;
                    resize = true;
                    break;
                // Add more cases for other keys as needed
            }
            is_rendering = true;
            update = true;
        }
    }
    if(update){
        this->paint(canvas);
    }
}

void Scene::renderFrame(Canvas& canvas, SDL_Renderer* renderer) {

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

int Scene::render(Canvas& canvas){
    int width = canvas.columns;
    int height = canvas.rows;

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
    is_rendering = false;

    while (is_running) {
        if(!is_rendering){
            //cout << "Handling input. is_rendering:" << is_rendering << endl;
            handleInput(event, canvas);
            renderFrame(canvas, renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}