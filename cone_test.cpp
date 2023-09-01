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
#include "headers/cylinder.h"
#include "headers/cylindrical_face.h"
#include "headers/cone.h"

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 3;

    Camera camera = Camera(Point(0, 0, 20), 1, -1, 1, -1, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);

    Cone cone = Cone(Point(0, 0, -100), Point(0, 20, -100), 10, Color(255, 0, 0));

    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background);

    scene.addObject(&cone);

    scene.paint(canvas);

    return canvas.render();
}