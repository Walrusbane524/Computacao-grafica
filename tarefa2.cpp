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
#include "headers/light.h"

using namespace std;

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 3;

    Camera camera = Camera(Point(0, 0, 0), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 2, 2, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);
    Material material = Material(Vec(0.5, 0.5, 0.5), Vec(0.5, 0.5, 0.5), 1);
    Sphere esfera = Sphere(Point(0, 0, -100), 20, Color(255, 0, 0), material);

    Light light = Light(Point(0, 5, 0), 0.7, 0.7, 0.7);

    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background, Vec(0.2, 0.2, 0.2));

    scene.addObject(&esfera);
    scene.addLight(&light);

    scene.paint(canvas);

    return canvas.render();
}