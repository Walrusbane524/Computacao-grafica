#define SDL_MAIN_HANDLED
#include <math.h>
#include <SDL2/SDL.h>
#include <iostream>

#include "headers/renderer.h"
#include "headers/camera.h"
#include "headers/scene.h"
#include "headers/canvas.h"
#include "headers/color.h"
#include "headers/point.h"
#include "headers/ray.h"
#include "headers/vec.h"
#include "headers/cylinder.h"
#include "headers/point_light.h"

int main(){

    int n_l = 50;
    int n_c = 50;
    double d = 60;

    Camera camera = Camera(100, 100, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

    Material material = Material(Vec(1, 1, 1),
                                 Vec(1, 1, 1),
                                 Vec(1,1,1),
                                 1);

    Cylinder cilindro = Cylinder(Point(0, -30, -200),
                                 Vector(0, 0.8, 0.45).normalize(),
                                 25, 60, material);

    Color background = Color(255, 204, 204);

    Scene scene = Scene(camera, background);
    PointLight light = PointLight(Point(40, 50, 40), 1, 0.1, 0.1);

    scene.addObject(&cilindro);
    scene.addLight(&light);
    scene.paint(canvas);

    Renderer renderer = Renderer(scene, canvas);
    renderer.start();
}
//
// Created by Murilo on 08/12/2023.
//
