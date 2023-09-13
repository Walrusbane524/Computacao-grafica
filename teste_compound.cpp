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
#include "headers/compound_object.h"
#include "headers/snowman.h"

using namespace std;

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 2.5;

    Camera camera = Camera(Point(0, 0, 20), 1, -1, 1, -1, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);

    SnowmanObject snm = SnowmanObject(Point(0, -40, -100));

    Light light = Light(Point(0, 100, -80), 1.0, 1.0, 1.0);

    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background, Vec(0.5, 0.5, 0.5));

    scene.addObject(&snm);
    scene.addLight(&light);

    scene.paint(canvas);

    return canvas.render();
}