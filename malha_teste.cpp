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

    int n_l = 500;
    int n_c = 500;
    double d = 1.;

    Camera camera = Camera(2, 2, n_l, n_c, d);
    camera.lookAt(Point(0, 0, 0), Point(0, 0, -100), Point(0, 200, 0));
    Canvas canvas = Canvas(n_l, n_c);

    /*
    Texture* car_texture = new Texture("assets/textures/uv_map_test.jpeg");
    cout << "Textura carregada." << endl;
    ObjMesh car = ObjMesh("assets/meshes/car.obj", car_texture);
    cout << "Carro carregado." << endl;

    car.transform(RotationMatrixYAxis(-1.57));
    car.transform(TranslationMatrix(Vector(0, 2, -10)));

    SphericalWrapper wrapped_car = SphericalWrapper(&car, -1);
    */
    
    Texture* squirtle_texture = new Texture("assets/textures/squirtle.jpeg");
    ObjMesh squirtle = ObjMesh("assets/meshes/squirtle.obj", squirtle_texture);

    Texture* porygon_texture = new Texture("assets/textures/porygon.png");
    ObjMesh porygon = ObjMesh("assets/meshes/porygon.obj", porygon_texture);

    Texture* charmander_texture = new Texture("assets/textures/charmander.jpeg");
    ObjMesh charmander = ObjMesh("assets/meshes/charmander.obj", charmander_texture);

    Texture* bulbasaur_texture = new Texture("assets/textures/bulbasaur.jpeg");
    ObjMesh bulbasaur = ObjMesh("assets/meshes/bulbasaur.obj", bulbasaur_texture);

    //mesh.transform(RotationMatrixYAxis(-1.57));
    squirtle.transform(RotationMatrixYAxis(0.35));
    squirtle.transform(TranslationMatrix(Vector(-30, -50, -200)));

    charmander.transform(RotationMatrixYAxis(-0.75));
    charmander.transform(TranslationMatrix(Vector(100, -50, -200)));

    porygon.transform(RotationMatrixYAxis(-0.55));
    porygon.transform(TranslationMatrix(Vector(30, -50, -200)));

    bulbasaur.transform(RotationMatrixYAxis(0.75));
    bulbasaur.transform(TranslationMatrix(Vector(-100, -50, -200)));

    SphericalWrapper wrapped_squirtle = SphericalWrapper(&squirtle, -1);
    SphericalWrapper wrapped_porygon = SphericalWrapper(&porygon, -1);
    SphericalWrapper wrapped_charmander = SphericalWrapper(&charmander, -1);
    SphericalWrapper wrapped_bulbasaur = SphericalWrapper(&bulbasaur, -1);
    //cout << "Finished" << endl;

    //printSphericalWrapperTree(wrapped_squirtle);
    //mesh.transform(TranslationMatrix(Vector(0, 0, -5)));
    
    
    Plane plane = Plane(
        Point(0, -50, 0), 
        Vector(0, 1, 0),
        Material(
            Vec(0.3, 0.6, 0.3),
            Vec(0.3, 0.8, 0.3),
            Vec(0.3, 1.0, 0.3),
            1
        )
    );
    Sphere sphere = Sphere(Point(0, 0, -200), 50);

    Color background = Color(100, 100, 255);

    Scene scene = Scene(camera, background);
    PointLight light = PointLight(Point(0, 100, 30), 1.0, 1.0, 1.0);

    //scene.addObject(&wrapped_car);
    scene.addObject(&wrapped_squirtle);
    scene.addObject(&wrapped_porygon);
    scene.addObject(&wrapped_charmander);
    scene.addObject(&wrapped_bulbasaur);
    //scene.addObject(wrapped_mesh.objects[1]);
    //scene.addObject(&wrapped_mesh.sphere);
    //scene.addObject(&sphere);
    scene.addObject(&plane);
    scene.addLight(&light);
    scene.paint(canvas);

    return scene.render(canvas);
}
