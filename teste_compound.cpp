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
#include "headers/tree.h"

using namespace std;

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 2.5;

    Camera camera = Camera(Point(0, 0, 20), Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, -1), 2, 2, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);

    SnowmanObject snm = SnowmanObject(Point(-5, -30, -150));
    TreeObject tr = TreeObject(Point(-60, -20, -150));

    Light light = Light(Point(0, 100, -80), 1.0, 1.0, 1.0);

    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background, Vec(0.5, 0.5, 0.5));

    scene.addObject(&snm);
    scene.addObject(&tr);
    scene.addLight(&light);

    scene.paint(canvas);

    return canvas.render();
}