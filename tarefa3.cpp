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
#include "headers/scene.h"
#include "headers/spot_light.h"
#include "headers/directional_light.h"
#include "headers/point_light.h"
#include "headers/plane.h"

using namespace std;

int main(){

    int n_l = 500;
    int n_c = 500;
    double d = 30;

    Camera camera = Camera(Point(0, 0, 0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 60, 60, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);
    
    Sphere esfera = Sphere(Point(0, 0, -100), 40, Material(Vec(0.7, 0.2, 0.2), Vec(0.7, 0.2, 0.2), Vec(0.7, 0.2, 0.2), 10));

    Plane chão = Plane(Point(0, -40, 0), Vector(0, 1, 0), Material(Vec(0, 0, 0), Vec(0.2, 0.7, 0.2), Vec(0.2, 0.7, 0.2), 1));

    Plane fundo = Plane(Point(0, 0, -200), Vector(0, 0, 1), Material(Vec(0, 0, 0), Vec(0.3, 0.3, 0.7), Vec(0.3, 0.3, 0.7), 1));

    PointLight point_light = PointLight(Point(0, 60, -30), 0.7, 0.7, 0.7);

    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background, Vec(0.3, 0.3, 0.3));

    scene.addObject(&esfera);
    scene.addObject(&chão);
    scene.addObject(&fundo);
    
    scene.addLight(&point_light);

    scene.paint(canvas);

    return canvas.render();
}