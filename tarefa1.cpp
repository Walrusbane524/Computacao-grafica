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

    Camera(Point position, double j_ymax, double j_ymin, double j_xmax, double j_xmin, double n_l, double n_c, double d){
        origin = position;
        this->j_xmax = j_xmax;
        this->j_xmin = j_xmin;
        this->j_ymax = j_ymax;
        this->j_ymin = j_ymin;
        this->n_l = n_l;
        this->n_c = n_c;
        this->d = d;
        delta_x = abs(j_xmax - j_xmin)/n_c;
        delta_y = abs(j_ymax - j_ymin)/n_l;
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

    optional<Point> colide(Ray ray){
        Vector w = ray.p_inicial - center;
        double a = ray.direction.scalar(ray.direction);
        double _b = w.scalar(ray.direction);
        double b = 2 * _b;
        double c = w.scalar(w) - pow(radius, 2);
        double delta = pow(b, 2) - 4 * a * c;

        if (delta >= 0){
            double root_1 = -_b + sqrt(delta);
            double answer = root_1;
            if (delta > 0){
                double root_2 = -_b - sqrt(delta);
                if (root_2 < root_1) answer = root_2;
            }
            return Point(ray.direction * answer);
        }
        else return nullopt;
    }
};

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 3;

    Camera camera = Camera(Point(0, 0, 0), 1, -1, 1, -1, n_l, n_c, -d);
    Canvas canvas = Canvas(n_l, n_c);
    Sphere sphere = Sphere(Point(0, 0, -100), 20, Color(255, 0, 0));
    Color background = Color(100, 100, 100);

    for(int l = 0; l < camera.n_l; l++){
        double y_l = camera.j_ymax - (camera.delta_y/2.0) - (l*camera.delta_y);
        for(int c = 0; c < camera.n_c; c++){
            double x_c = camera.j_xmin + (camera.delta_x/2.0) + (c*camera.delta_x);
            Point p_j = Point(x_c, y_l, -d);
            Ray ray = Ray(camera.origin, p_j);
            if (sphere.colide(ray)){
                canvas.matrix[l][c] = sphere.color;
            }
            else{
                canvas.matrix[l][c] = background;
            }
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