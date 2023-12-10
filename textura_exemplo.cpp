#define SDL_MAIN_HANDLED
#include <math.h>
#include <optional>
#include <SDL2/SDL.h>
#include <iostream>
#include <limits>
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
#include "headers/texture.h"
#include "headers/point_light.h"
#include "headers/sphere.h"
#include "headers/textured_sphere.h"
#include "headers/obj_mesh.h"
#include "headers/plane.h"
#include "headers/textured_plane.h"

int main(){

    int n_l = 50;
    int n_c = 50;
    double d = 60;

    Camera camera = Camera(100, 100, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

    Material pokeball_material = Material(
            Vec(0.1, 0.1, 0.1),
            Vec(0.7, 0.7, 0.7),
            Vec(0.8, 0.8, 0.8),
            30
    );

    Texture* pokeball_texture = new Texture("assets/textures/pokeball.jpg");

    Texture* bulbasaur_texture = new Texture("assets/textures/bulbasaur.jpeg");
    ObjMesh bulbasaur = ObjMesh("assets/meshes/bulbasaur.obj", bulbasaur_texture);

    bulbasaur.transform(RotationMatrixYAxis(3.14));
    bulbasaur.transform(TranslationMatrix(Vector(50, -20, -200)));

    SphericalWrapper wrapped_bulbasaur = SphericalWrapper(&bulbasaur, -1);

    Sphere sphere = Sphere(
            Point(-50, -10, -200),
            15,
            pokeball_material
    );

    Plane wall = Plane(
            Point(0, 0, -300),
            Vector(0, 0, 1),
            Material(
                    Vec(0.4, 0.4, 0.4),
                    Vec(0.8, 0.8, 0.8),
                    Vec(0.8, 0.8, 0.8),
                    1
            )
    );

    Texture* wood = new Texture("assets/textures/wood.jpg");

    TexturedPlane wall = TexturedPlane(wood, Vector(10, 0, 0), ceiling_texture, 3000);

    TexturedSphere pokeball = TexturedSphere(sphere, pokeball_texture);
    pokeball.rotation_matrix = new RotationMatrixYAxis(1.57);

    PointLight light = PointLight(Point(0, 20, -100), 1, 1, 1);

    Color background = Color(100, 100, 255);

    Scene scene = Scene(camera, background);
    scene.addObject(&pokeball);
    scene.addObject(&wall);
    scene.addObject(&wrapped_bulbasaur);
    scene.addLight(&light);
    scene.paint(canvas);

    Renderer renderer = Renderer(scene, canvas);
    renderer.start();
}
//
// Created by Murilo on 10/12/2023.
//
