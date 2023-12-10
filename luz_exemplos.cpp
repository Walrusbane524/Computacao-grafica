#define SDL_MAIN_HANDLED
#include <math.h>
#include <optional>
#include <SDL2/SDL.h>
#include <iostream>
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
#include "headers/point_light.h"
#include "headers/renderer.h"
#include "headers/spot_light.h"
#include "headers/directional_light.h"

int main(){

    int n_l = 50;
    int n_c = 50;
    double d = 60;
    int light_type;
    cout << "Tipo de Luz: \n   1 - Pontual;\n   2 - Spot;\n   3 - Direcional:\n";
    cin >> light_type;

    Light* light;

    switch (light_type) {
        case 1:
            light = new PointLight(Point(0, 20, -5), 0.5, 0.5, 0.5);
            break;
        case 2:
            light = new SpotLight(Point(0, 20, -5),
                                           Vector(0, 0.5, 1),
                                           10, 0.5, 0.5, 0.5);
            break;
        case 3:
            light = new DirectionalLight(Vector(0, -1, -1), 1, 1, 1);
            break;
        default:
            cout << "Luz inválida!";
            return -1;
    }

    Camera camera = Camera(100, 100, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

    Material material = Material(Vec(0.8, 0.05, 0.8),
                                 Vec(0.7, 0.05, 0.7),
                                 Vec(0.8,0.8,0.8),
                                 2);

    Sphere esfera = Sphere(Point(0, 0, -50), 15, material);

    Plane plane = Plane(
            Point(0, 0, -200),
            Vector(0, 0, 1),
            Material(
                    Vec(0.8, 0.5, 0),
                    Vec(1., 0.4, 0.1),
                    Vec(1., 1., 1.),
                    1
            )
    );

    Color background = Color(100, 100, 255);
    Scene scene = Scene(camera, background);

    scene.addObject(&esfera);
    scene.addObject(&plane);
    scene.addLight(&(*light));
    scene.paint(canvas);

    Renderer renderer = Renderer(scene, canvas);
    renderer.start();
}
//
// Created by Murilo on 09/12/2023.
//
