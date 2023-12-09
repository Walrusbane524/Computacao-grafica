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

int main(){

    int n_l = 50;
    int n_c = 50;
    double d = 60;

    Camera camera = Camera(100, 100, n_l, n_c, d);
    camera.lookAt(Point(500, 100, 500), Point(500, 100, 1000), Point(500, 200, 500));
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
    
    Texture* squirtle_texture = new Texture("assets/textures/squirtle.jpeg");
    ObjMesh squirtle = ObjMesh("assets/meshes/squirtle.obj", squirtle_texture);

    cout << "Squirtle loaded" << endl;
    Texture* porygon_texture = new Texture("assets/textures/porygon.png");
    ObjMesh porygon = ObjMesh("assets/meshes/porygon.obj", porygon_texture);
    cout << porygon.triangles[0].normals.size() << endl;
    cout << "Porygon loaded" << endl;

    Texture* charmander_texture = new Texture("assets/textures/charmander.jpeg");
    ObjMesh charmander = ObjMesh("assets/meshes/charmander.obj", charmander_texture);
    cout << "Charmander loaded" << endl;

    Texture* bulbasaur_texture = new Texture("assets/textures/bulbasaur.jpeg");
    ObjMesh bulbasaur = ObjMesh("assets/meshes/bulbasaur.obj", bulbasaur_texture);
    cout << "Bulbasaur loaded" << endl;

    Texture* porygon_machine_texture = new Texture("assets/textures/porygon_machine.jpeg");
    ObjMesh porygon_machine = ObjMesh("assets/meshes/porygon_machine.obj", porygon_machine_texture);
    cout << "Porygon machine loaded" << endl;

    Texture* bookshelf_texture = new Texture("assets/textures/bookshelf.jpeg");
    ObjMesh bookshelf = ObjMesh("assets/meshes/bookshelf.obj", bookshelf_texture);
    cout << "Bookshelf loaded" << endl;

    //squirtle.transform(ScaleMatrix(Vec(0.5, 0.5, 0.5)));
    squirtle.transform(RotationMatrixYAxis(0.35));
    //squirtle.transform(RotationMatrixUAxis(Vector(0, 1, 0), 0.35));    
    squirtle.transform(TranslationMatrix(Vector(-30, -50, -200)));

    charmander.transform(RotationMatrixYAxis(-0.75));
    charmander.transform(TranslationMatrix(Vector(100, -50, -200)));

    porygon.transform(RotationMatrixYAxis(-0.55));
    porygon.transform(TranslationMatrix(Vector(30, -50, -200)));

    bulbasaur.transform(RotationMatrixYAxis(0.75));
    bulbasaur.transform(TranslationMatrix(Vector(-100, -50, -200)));

    //porygon_machine.transform(RotationMatrixYAxis(0.75));
    porygon_machine.transform(TranslationMatrix(Vector(0, -50, -400)));
    
    bookshelf.transform(RotationMatrixYAxis(0.75));
    bookshelf.transform(TranslationMatrix(Vector(-100, -50, -400)));

    cout << "Meshes moved" << endl;

    SphericalWrapper wrapped_squirtle = SphericalWrapper(&squirtle, -1);
    SphericalWrapper wrapped_porygon = SphericalWrapper(&porygon, -1);
    SphericalWrapper wrapped_charmander = SphericalWrapper(&charmander, -1);
    SphericalWrapper wrapped_bulbasaur = SphericalWrapper(&bulbasaur, -1);
    SphericalWrapper wrapped_porygon_machine = SphericalWrapper(&porygon_machine, -1);
    SphericalWrapper wrapped_bookshelf = SphericalWrapper(&bookshelf, -1);

    cout << "Meshes wrapped" << endl;

    //printSphericalWrapperTree(wrapped_bulbasaur);

    //cout << "Finished" << endl;

    //printSphericalWrapperTree(wrapped_squirtle);
    //mesh.transform(TranslationMatrix(Vector(0, 0, -5)));

    Texture* floor_texture = new Texture("assets/textures/wood.jpg");

    //cout << plane_texture->image[0][0].r << endl;
    Plane floor_plane = Plane(
        Point(0, 0, 0), 
        Vector(0, 1, 0),
        Material(
            Vec(1., 1., 1.),
            Vec(1., 1., 1.),
            Vec(1., 1., 1.),
            1
        )
    );
    TexturedPlane floor = TexturedPlane(floor_plane, Vector(0, 0, 10), floor_texture, 10000);

    Material wall_material = Material(
        Vec(0.2, 0.2, 0.2),
        Vec(0.7, 0.7, 0.7),
        Vec(0.8, 0.8, 0.8),
        1
    );


    Texture* wall_texture = new Texture("assets/textures/white-wall.jpg");

    Plane north_wall_plane = Plane(
        Point(0, 0, 1000), 
        Vector(0, 0, -1),
        wall_material
    );

    TexturedPlane north_wall = TexturedPlane(north_wall_plane, Vector(0, 10, 0), wall_texture, 30000);

    Plane south_wall_plane = Plane(
        Point(0, 0, 0), 
        Vector(0, 0, 1),
        wall_material
    );

    TexturedPlane south_wall = TexturedPlane(south_wall_plane, Vector(0, 10, 0), wall_texture, 30000);

    Plane east_wall_plane = Plane(
        Point(0, 0, 0), 
        Vector(1, 0, 0),
        wall_material
    );

    TexturedPlane east_wall = TexturedPlane(east_wall_plane, Vector(0, 10, 0), wall_texture, 30000);

    Plane west_wall_plane = Plane(
        Point(1000, 0, 0), 
        Vector(-1, 0, 0),
        wall_material
    );

    TexturedPlane west_wall = TexturedPlane(west_wall_plane, Vector(0, 10, 0), wall_texture, 30000);

    Texture* ceiling_texture = new Texture("assets/textures/ceiling.jpg");

    Plane ceiling_plane = Plane(
        Point(0, 500, 0), 
        Vector(0, -1, 0),
        Material(
            Vec(0.4, 0.4, 0.4),
            Vec(0.8, 0.8, 0.8),
            Vec(0.8, 0.8, 0.8),
            1
        )
    );

    TexturedPlane ceiling = TexturedPlane(ceiling_plane, Vector(10, 0, 0), ceiling_texture, 30000);

    Texture* pokeball_texture = new Texture("assets/textures/pokeball.jpg");
    Sphere pokeball_sphere = Sphere(Point(0, 0, -100), 5);

    TexturedSphere pokeball = TexturedSphere(pokeball_sphere, pokeball_texture);
    pokeball.rotation_matrix = new RotationMatrixYAxis(1.5);


    Color background = Color(100, 100, 255);

    Vec ambient = Vec(0.5, 0.5, 0.5);

    Scene scene = Scene(camera, background, ambient);
    PointLight light = PointLight(Point(500, 490, 500), 1.0, 1.0, 1.0);

    //scene.addObject(&pokeball);
    //scene.addObject(&wrapped_squirtle);
    //scene.addObject(&wrapped_porygon);
    //scene.addObject(&wrapped_charmander);
    //scene.addObject(&wrapped_bulbasaur);
    //scene.addObject(&wrapped_porygon_machine);
    //scene.addObject(&wrapped_bookshelf);
    scene.addObject(&floor);
    scene.addObject(&north_wall);
    scene.addObject(&south_wall);
    scene.addObject(&east_wall);
    scene.addObject(&west_wall);
    scene.addObject(&ceiling);
    scene.addLight(&light);
    scene.paint(canvas);

    Renderer renderer = Renderer(scene, canvas);
    renderer.start();
    //return scene.render(canvas);
}