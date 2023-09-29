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
#include "headers/plane.h"
#include "headers/triangle.h"

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 2.5;

    Camera camera = Camera(Point(0, 0, 20), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 2, 2, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);

    Material material = Material();

    Triangle triangle = Triangle(Vector(0, 0, 1), Point(-20, -10, -100), Point(20, -10, -100), Point(0, 20, -100), material);

    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background);
    Light light = Light(Point(100, 100, -100), 1.0, 1.0, 1.0);

    scene.addObject(&triangle);
    scene.addLight(&light);

    Ray ray = Ray(Point(0, 0, 0), Vector(0, 0, -1));

    triangle.colide(ray);

    scene.paint(canvas);

    return canvas.render();
}
