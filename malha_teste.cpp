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
#include "headers/textured_mesh.h"

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 2.;

    Camera camera = Camera(2, 2, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

/*
    vector<Point> points;
    points.push_back(Point(0, 0, -10));
    points.push_back(Point(0, -10, -10));
    points.push_back(Point(-10, -10, -10));

    points.push_back(Point(10, 0, -10));
    points.push_back(Point(10, -10, -10));
    points.push_back(Point(0, -10, -10));

    vector<vector<int>> faces = {
        {0, 1, 2},
        {3, 4, 5},
    };

    Mesh mesh = Mesh(points, faces);
*/

    //ObjMesh mesh = ObjMesh("assets/meshes/Porygon.obj");
    TexturedMesh mesh = TexturedMesh("assets/meshes/Porygon.obj", "assets/textures/pm0137_00_Eye1.png");

    mesh.transform(RotationMatrixYAxis(1.57));
    mesh.transform(TranslationMatrix(Vector(0, -50, -200)));

    Color background = Color(0, 0, 0);

    Scene scene = Scene(camera, background);
    PointLight light = PointLight(Point(0, 100, -30), 1.0, 1.0, 1.0);

    scene.addObject(&mesh);
    scene.addLight(&light);

    scene.paint(canvas);

    return canvas.render();
}
