//
// Created by Murilo on 08/12/2023.
//
#define SDL_MAIN_HANDLED
#include <math.h>
#include <optional>
#include <SDL2/SDL.h>
#include <iostream>
#include <limits>
#include "headers/cone.h"
#include "headers/cylinder.h"
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
#include "headers/mesh.h"
#include "headers/obj_mesh.h"
#include "headers/point_light.h"
#include "headers/translation_matrix.h"
#include "headers/rotation_matrix_y_axis.h"
#include "headers/rotation_matrix_u_axis.h"
#include "headers/spherical_wrapper.h"
#include "headers/renderer.h"
#include "headers/scale_matrix.h"
#include "headers/textured_plane.h"
#include "headers/textured_sphere.h"

int main(){

    int n_l = 50;
    int n_c = 50;
    double d = 60;

    Camera camera = Camera(100, 100, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

    /*
    Texture* test_texture = new Texture("assets/textures/uv_map_test.jpeg");

    ObjMesh cube = ObjMesh("assets/meshes/cube.obj", test_texture);
    ObjMesh smooth_cube = ObjMesh("assets/meshes/smooth_cube.obj", test_texture);

    cube.transform(TranslationMatrix(Vector(-2, 0, -10)));
    smooth_cube.transform(TranslationMatrix(Vector(2, 0, -10)));

    SphericalWrapper wrapped_cube = SphericalWrapper(&cube, -1);
    SphericalWrapper wrapped_smooth_cube = SphericalWrapper(&smooth_cube, -1);
    */
    //printSphericalWrapperTree(wrapped_bulbasaur);

    //cout << "Finished" << endl;

    //printSphericalWrapperTree(wrapped_squirtle);
    //mesh.transform(TranslationMatrix(Vector(0, 0, -5)));

    Material material = Material(Vec(0.2, 0.5, 0.8),
                                 Vec(0.2, 0.5, 0.6),
                                 Vec(0.8,0.1,0.8),
                                 10);


    Cone cone = Cone(Point(0, 0, -100),
                                 Point(0, 50, -110),
                                 15, material);

    Color background = Color(255, 204, 204);

    Scene scene = Scene(camera, background);
    PointLight light = PointLight(Point(40, 50, 40), 1.0, 1.0, 1.0);

    scene.addObject(&cone);
    /*
    scene.addObject(&wrapped_cube);
    scene.addObject(&wrapped_smooth_cube);
    */
    scene.addLight(&light);
    scene.paint(canvas);

    Renderer renderer = Renderer(scene, canvas);
    renderer.start();
    //return scene.render(canvas);
}
//
//
// Created by Murilo on 08/12/2023.
//
