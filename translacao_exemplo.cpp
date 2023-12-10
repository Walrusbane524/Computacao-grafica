#define SDL_MAIN_HANDLED
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
#include "headers/directional_light.h"

void printSphericalWrapperTree(const SphericalWrapper& wrapper, int depth = 0) {
    // Print information about the current node (SphericalWrapper)
    try{
        cout << std::string(2 * depth, ' ') << "Node: ";
        cout << "Sphere radius: " << wrapper.sphere.radius << std::endl;
    }
    catch(...){
        cout << "Sphere error" << endl;
    }

    // Print information about each child (Object or SphericalWrapper)
    for (const auto& obj : wrapper.objects) {
        try{
            if (const SphericalWrapper* childWrapper = dynamic_cast<const SphericalWrapper*>(obj)) {
                // Recursive call for SphericalWrapper child

                printSphericalWrapperTree(*childWrapper, depth + 1);

            } else {
                if(const ObjMesh* childWrapper = dynamic_cast<const ObjMesh*>(obj))
                    cout << string(2 * (depth + 1), ' ') << "Child mesh size: " << childWrapper->triangles.size() << endl;
                else
                    cout << string(2 * (depth + 1), ' ') << "Child Object: " << 1 << endl;
            }
        }
        catch(...){
            cout << "SubObject error " << endl;
        }
    }
}

int main(){

    int n_l = 50;
    int n_c = 50;
    double d = 60;

    Camera camera = Camera(100, 100, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

    Texture* cube_texture = new Texture("assets/textures/uv_map_test.jpeg");
    ObjMesh cube = ObjMesh("assets/meshes/cube.obj", cube_texture);
    ObjMesh cube2 = ObjMesh("assets/meshes/cube.obj", cube_texture);

    cout << "Porygons loaded" << endl;

    cube.transform(RotationMatrixYAxis(3.14));
    cube.transform(TranslationMatrix(Vector(-3, 0, -10)));

    cube2.transform(RotationMatrixYAxis(3.14));
    cube2.transform(ScaleMatrix(Vec(2, 2,2)));
    cube2.transform(TranslationMatrix(Vector(3, 0, -10)));

    cout << "Meshes moved" << endl;

    SphericalWrapper wrapped_porygon = SphericalWrapper(&cube, -1);
    SphericalWrapper wrapped_porygon2 = SphericalWrapper(&cube2, -1);

    cout << "Meshes wrapped" << endl;

    Color background = Color(100, 100, 255);

    Scene scene = Scene(camera, background);
    //DirectionalLight light = DirectionalLight(Vector(0, 0, -1), 1, 1, 1);
    PointLight light = PointLight(Point(0, 0, 0), 1.0, 1.0, 1.0);

    scene.addObject(&wrapped_porygon);
    scene.addObject(&wrapped_porygon2);

    scene.addLight(&light);
    scene.paint(canvas);

    Renderer renderer = Renderer(scene, canvas);
    renderer.start();
}
//
// Created by Murilo on 09/12/2023.
//
