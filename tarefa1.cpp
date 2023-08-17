#include <math.h>
#include <optional>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Vec{
    protected:
        double x, y, z;
    
    public:
        Vec(){
            x = 0;
            y = 0;
            z = 0;
        }
        Vec(double x, double y, double z){
            this->x = x;
            this->y = y;
            this->z = z;
        }

        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        double getZ(){
            return z;
        }

        Vec operator+(Vec v){
            return Vec(v.x + x, v.y + y, v.z + z);
        }
        Vec operator-(Vec v){
            return Vec(v.x - x, v.y - y, v.z - z);
        }
        Vec operator*(double d){
            return Vec(x * d, y * d, z * d);
        }
        Vec operator/(double d){
            return Vec(x / d, y / d, z / d);
        }
        double scalar(Vec v){
            return v.x * x + v.y * y + v.z * z;
        }
        double modulo(){
            return sqrt(this->scalar(*this));
        }

    
};

class Point: public Vec{
    public:

    Point() : Vec(0, 0, 0){}
    Point(Vec v): Vec(v.getX(), v.getY(), v.getZ()){}
    Point(double x, double y, double z) : Vec(x, y, z){}
};

class Vector: public Vec{
    public:
    Vector() : Vec(0, 0, 0){}
    Vector(Vec v) : Vec(v.getX(), v.getY(), v.getZ()){}
    Vector(Point p) : Vec(p.getX(), p.getY(), p.getZ()){}
    Vector(double x, double y, double z) : Vec(x, y, z){}

};

class Color{
    public:

    int r;
    int g;
    int b;

    Color(){
        r = 0;
        g = 0;
        b = 0;
    }
    Color(int r, int g, int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

class Camera{
    public:

    Point origin;
    double j_ymax;
    double j_ymin;
    double j_xmax;
    double j_xmin;
    double n_l;
    double n_c;
    double d;
    double delta_x;
    double delta_y;

    Camera(double j_ymax, double j_ymin, double j_xmax, double j_xmin, double n_l, double n_c, double d){
        origin = Point(0, 0, 0);
        this->j_xmax = j_xmax;
        this->j_xmin = j_xmin;
        this->j_ymax = j_ymax;
        this->j_ymin = j_ymin;
        this->n_l = n_l;
        this->n_c = n_c;
        this->d = d;
        delta_x = abs(j_xmax - j_xmin);
        delta_y = abs(j_ymax - j_ymin);
    }
};

class Canvas{
    public:
    Color** matrix;
    int rows;
    int columns;

    Canvas(){
        rows = 0;
        columns = 0;
        matrix = nullptr;
    }
    Canvas(int n_l, int n_c){
        rows = n_l;
        columns = n_c;
        matrix = new Color*[n_l];
        for (int i = 0; i < n_l; i++)
            matrix[i] = new Color[n_c];
    }

    ~Canvas() {
        if (matrix != nullptr) {
            for (int i = 0; i < rows; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }
    /*
    SDL_Color convertColor(const Color& color) {
        SDL_Color sdlColor;
        sdlColor.r = color.r;
        sdlColor.g = color.g;
        sdlColor.b = color.b;
        sdlColor.a = 255; // Assuming full opacity
        return sdlColor;
    }

    void render(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
        int cellWidth = windowWidth / columns;
        int cellHeight = windowHeight / rows;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                SDL_Rect rect = {j * cellWidth, i * cellHeight, cellWidth, cellHeight};
                SDL_Color sdlColor = convertColor(matrix[i][j]);
                SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    */
};

class Ray{
    public:
    Point p_inicial;
    Vector direction;

    Ray(){
        p_inicial = Point();
        direction = Vector(0, 0, -1);
    }
    Ray(Point p_inicial, Vector direction){
        this->p_inicial = p_inicial;
        this->direction = direction;
    }
    Ray(Point p_inicial, Point p_ray){
        this->p_inicial = p_inicial;
        this->direction = (p_ray - p_inicial) / ((p_ray - p_inicial).modulo());
    }
};

class Sphere{
    public:
    Point center;
    double radius;
    Color color;

    Sphere(){
        center = Point();
        radius = 1;
        color = Color(255, 0, 0);
    }
    Sphere(Point center, double radius, Color color){
        this->center = center;
        this->radius = radius;
        this->color = color;
    }

    optional<double> colide(Ray ray){
        Vector w = ray.p_inicial - center;
        double a = ray.direction.scalar(ray.direction);
        double _b = w.scalar(ray.direction);
        double b = 2 * _b;
        double c = w.scalar(w) - pow(radius, 2);
        double delta = pow(_b, 2) - 4 * a * c;

        if (delta >= 0){
            double root_1 = -_b + sqrt(delta);
            double answer = root_1;
            if (delta > 0){
                double root_2 = -_b - sqrt(delta);
                if (root_2 > root_1) answer = root_2;
            }
            return answer;
        }
        else return nullopt;
    }
};

int main(){

    int n_l = 200;
    int n_c = 200;
    double d = 15;

    Camera camera = Camera(1, -1, 1, -1, n_l, n_c, -d);
    Canvas canvas = Canvas(n_l, n_c);
    Sphere sphere = Sphere(Point(0, 0, -100), 99.93, Color(255, 0, 0));

    for(int l = 0; l < camera.n_l; l++){
        double y_l = camera.j_ymax - (camera.delta_y/2) - (l*camera.delta_y);
        for(int c = 0; c < camera.n_c; c++){
            double x_c = camera.j_xmin + (camera.delta_x/2) + (c*camera.delta_x);
            Point p_j = Point(x_c, y_l, -d);
            Ray ray = Ray(camera.origin, p_j);
            if (sphere.colide(ray)){
                canvas.matrix[l][c] = sphere.color;
                cout << "#";
            }
            else{
                canvas.matrix[l][c] = Color();
                cout << " ";
            }
        }
        cout << "\n";
    }

    int width = n_l;
    int height = n_c;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // Handle initialization error
        return 1;
    }

    // Create a window and renderer
    SDL_Window* window = SDL_CreateWindow("Color Matrix", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        // Handle window creation error
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        // Handle renderer creation error
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Event loop
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the colors
        for (int y = 0; y < canvas.rows; ++y) {
            for (int x = 0; x < canvas.columns; ++x) {
                Color color = canvas.matrix[y][x];  // Assuming you have a Color class with r, g, b attributes

                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        // Update the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    /*
    SDL_Init(SDL_INIT_VIDEO);

    int windowWidth = 800;
    int windowHeight = 800;
    SDL_Window* window = SDL_CreateWindow("Canvas Display", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the canvas
        canvas.render(renderer, windowWidth, windowHeight);

        // Update the renderer
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    */

    return 0;
}