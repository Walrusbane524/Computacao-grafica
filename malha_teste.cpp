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
#include "headers/spherical_wrapper.h"
/*
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
*/
int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 2.5;

    Camera camera = Camera(2, 2, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

    Texture* texture = new Texture("assets/textures/porygon_body.png");

    ObjMesh mesh = ObjMesh("assets/meshes/porygon.obj", texture);

    //mesh.transform(RotationMatrixYAxis(-1.57));
    mesh.transform(RotationMatrixYAxis(-0.75));
    mesh.transform(TranslationMatrix(Vector(0, -50, -200)));

    SphericalWrapper wrapped_mesh = SphericalWrapper(&mesh, -1);
    //cout << "Finished" << endl;

    //printSphericalWrapperTree(wrapped_mesh);
    //mesh.transform(TranslationMatrix(Vector(0, 0, -5)));
    
    Color background = Color(0, 0, 0);

    Scene scene = Scene(camera, background);
    PointLight light = PointLight(Point(0, 100, -30), 1.0, 1.0, 1.0);

    scene.addObject(&wrapped_mesh);
    //scene.addObject(wrapped_mesh.objects[1]);
    scene.addLight(&light);
    scene.paint(canvas);

    return canvas.render();
}
