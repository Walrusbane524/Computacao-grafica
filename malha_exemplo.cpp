#define SDL_MAIN_HANDLED
#include <math.h>
#include <optional>
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
#include "headers/point_light.h"
#include "headers/sphere.h"
#include "headers/spherical_wrapper.h"
#include "headers/translation_matrix.h"
#include "headers/rotation_matrix_y_axis.h"
#include "headers/material.h"
#include "headers/point_light.h"
#include "headers/obj_mesh.h"

int main(){

    int n_l = 50;
    int n_c = 50;
    double d = 60;

    Camera camera = Camera(100, 100, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

    Texture* porygon_texture = new Texture("assets/textures/porygon.png");
    ObjMesh porygon = ObjMesh("assets/meshes/porygon.obj", porygon_texture);
    cout << "Porygon loaded" << endl;

    porygon.transform(RotationMatrixYAxis(-0.55));
    porygon.transform(TranslationMatrix(Vector(0, -50, -150)));

    cout << "Meshes moved" << endl;

    SphericalWrapper wrapped_porygon = SphericalWrapper(&porygon, -1);

    cout << "Meshes wrapped" << endl;

    Color background = Color(100, 100, 255);

    Scene scene = Scene(camera, background);
    PointLight light = PointLight(Point(0, 100, 30), 1.0, 1.0, 1.0);

    scene.addObject(&wrapped_porygon);
    scene.addLight(&light);
    scene.paint(canvas);

    Renderer renderer = Renderer(scene, canvas);
    renderer.start();
}
