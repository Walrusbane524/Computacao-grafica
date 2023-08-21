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

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 3;

    Camera camera = Camera(Point(0, 0, 20), 1, -1, 1, -1, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);
    Sphere esfera1 = Sphere(Point(0,  25, -100), 10, Color(255, 255, 255));
    Sphere esfera2 = Sphere(Point(0,   5, -100), 15, Color(255, 255, 255));
    Sphere esfera3 = Sphere(Point(0, -20, -100), 20, Color(255, 255, 255));
    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background);

    scene.addObject(&esfera1);
    scene.addObject(&esfera2);
    scene.addObject(&esfera3);

    scene.paint(canvas);

    return canvas.render();
}