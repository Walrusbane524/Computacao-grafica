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

using namespace std;

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 3;

    Camera camera = Camera(Point(0, 0, 0), 1, -1, 1, -1, n_l, n_c, -d);
    Canvas canvas = Canvas(n_l, n_c);
    Sphere esfera = Sphere(Point(0, 0, -100), 20, Color(255, 0, 0));
    Object* objetos[1];
    objetos[0] = &esfera;
    Color background = Color(100, 100, 100);

    for(int l = 0; l < camera.n_l; l++){
        double y_l = camera.j_ymax - (camera.delta_y/2.0) - (l*camera.delta_y);
        
        for(int c = 0; c < camera.n_c; c++){
            double x_c = camera.j_xmin + (camera.delta_x/2.0) + (c*camera.delta_x);

            Point p_j = Point(x_c, y_l, camera.origin.z - d);
            Ray ray = Ray(camera.origin, p_j);

            Color cor_atual = background;
            double smallest_root = numeric_limits<double>::infinity();

            for(Object* s : objetos){
                optional<double> intersect = s->colide(ray);
                if (intersect.has_value()){
                    double root = intersect.value();
                    if(root < smallest_root){
                        root = smallest_root;
                        cor_atual = s->color;
                    }
                }
            }
            canvas.matrix[l][c] = cor_atual;
        }
    }

    return canvas.render();
}