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
#include "headers/cylinder.h"
#include "headers/plane.h"

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 2.5;

    Camera camera = Camera(Point(0, 0, 20), 1, -1, 1, -1, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);
    Sphere esfera1 = Sphere(Point(0,  25, -100), 10, Color(255, 255, 255));
    Sphere esfera2 = Sphere(Point(0,   5, -100), 15, Color(255, 255, 255));
    Sphere esfera3 = Sphere(Point(0, -20, -100), 20, Color(255, 255, 255));
    Cylinder braco_direito = Cylinder(Point(12, 5, -100), Vector(0.9, -0.1, 0).normalize(), 2, 20, Color(205, 133, 63));
    Cylinder braco_esquerdo = Cylinder(Point(-12, 5, -100), Vector(-0.9, -0.1, 0).normalize(), 2, 20, Color(205, 133, 63));
    Plane plano = Plane(Point(0, -40, -100), Vector(0, 1, 0), Color(70, 130, 180));
    
    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background);

    scene.addObject(&esfera1);
    scene.addObject(&esfera2);
    scene.addObject(&esfera3);
    scene.addObject(&braco_direito);
    scene.addObject(&braco_esquerdo);
    scene.addObject(&plano);

    scene.paint(canvas);

    return canvas.render();
}