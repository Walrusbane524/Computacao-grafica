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
    double d = 3;

    Camera camera = Camera(Point(0, 0, 20), 1, -1, 1, -1, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);

    Triangle triangle = Triangle();

    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background);
    Light light = Light(Point(100, 100, -100), 1.0, 1.0, 1.0);

    scene.addObject(&triangle);
    scene.addLight(&light);

    scene.paint(canvas);


    return canvas.render();
}
