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

    ObjMesh computer_table = ObjMesh("assets/meshes/mesa.obj", bookshelf_texture);

    ObjMesh pokemon_table = computer_table;

    Texture* computer_texture = new Texture("assets/textures/computer.jpeg");
    ObjMesh computer = ObjMesh("assets/meshes/computer.obj", computer_texture);

    Texture* heal_machine_texture = new Texture("assets/textures/heal_machine.jpeg");
    ObjMesh heal_machine = ObjMesh("assets/meshes/heal_machine.obj", heal_machine_texture);

    pokemon_table.transform(TranslationMatrix(Vector(320, 0, 700)));
    squirtle.transform(  TranslationMatrix(Vector(320 - 70, 0, 700 - 100)));
    charmander.transform(TranslationMatrix(Vector(320 + 70, 0, 700 - 100)));
    bulbasaur.transform( TranslationMatrix(Vector(     320, 0, 700 - 100)));

    porygon_machine.transform(TranslationMatrix(Vector(800, 0, 700)));
    porygon.transform(TranslationMatrix(Vector(800, 120, 700)));
    
    //bookshelf.transform(RotationMatrixYAxis(0.75));
    bookshelf.transform(TranslationMatrix(Vector(175, 0, 965)));

    computer_table.transform(TranslationMatrix(Vector(725, 0, 950)));
    
    computer.transform(TranslationMatrix(Vector(725, 100, 950)));

    heal_machine.transform(TranslationMatrix(Vector(925, 0, 925)));

    cout << "Meshes moved" << endl;

    SphericalWrapper wrapped_squirtle = SphericalWrapper(&squirtle, -1);
    SphericalWrapper wrapped_porygon = SphericalWrapper(&porygon, -1);
    SphericalWrapper wrapped_charmander = SphericalWrapper(&charmander, -1);
    SphericalWrapper wrapped_bulbasaur = SphericalWrapper(&bulbasaur, -1);
    SphericalWrapper wrapped_porygon_machine = SphericalWrapper(&porygon_machine, -1);
    SphericalWrapper wrapped_bookshelf = SphericalWrapper(&bookshelf, -1);
    SphericalWrapper wrapped_computer_table = SphericalWrapper(&computer_table, -1);
    SphericalWrapper wrapped_pokemon_table = SphericalWrapper(&pokemon_table, -1);
    SphericalWrapper wrapped_computer = SphericalWrapper(&computer, -1);
    SphericalWrapper wrapped_heal_machine = SphericalWrapper(&heal_machine, -1);

    cout << "Meshes wrapped" << endl;

    Material pokeball_material = Material(
        Vec(0.1, 0.1, 0.1),
        Vec(0.7, 0.7, 0.7),
        Vec(0.8, 0.8, 0.8),
        30
    );

    Texture* pokeball_texture = new Texture("assets/textures/pokeball.jpg");

    Sphere sphere_1 = Sphere(
        Point(925 + 21, 80, 925 + 27),
        9,
        pokeball_material
    );

    TexturedSphere pokeball_1 = TexturedSphere(sphere_1, pokeball_texture);

    Sphere sphere_2 = Sphere(
        Point(925 - 21, 80, 925 + 27),
        9,
        pokeball_material
    );

    TexturedSphere pokeball_2 = TexturedSphere(sphere_2, pokeball_texture);

    Sphere sphere_3 = Sphere(
        Point(925 + 21, 80, 925 + 5),
        9,
        pokeball_material
    );

    TexturedSphere pokeball_3 = TexturedSphere(sphere_3, pokeball_texture);

    Matrix* pokeballs_rotation_matrix = new RotationMatrixYAxis(-1.5708);

    pokeball_1.rotation_matrix = pokeballs_rotation_matrix;
    pokeball_2.rotation_matrix = pokeballs_rotation_matrix;
    pokeball_3.rotation_matrix = pokeballs_rotation_matrix;

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

    TexturedPlane ceiling = TexturedPlane(ceiling_plane, Vector(10, 0, 0), ceiling_texture, 3000);


    Color background = Color(100, 100, 255);

    Vec ambient = Vec(0.5, 0.5, 0.5);

    Scene scene = Scene(camera, background, ambient);
    PointLight light = PointLight(Point(500, 490, 500), 0.8, 0.8, 0.8);
    PointLight porygon_machine_light = PointLight(Point(800, 185, 700), 0, 0, 1.0);

    //scene.addObject(&pokeball);
    //scene.addObject(&wrapped_porygon_machine);
    scene.addObject(&floor);
    scene.addObject(&north_wall);
    scene.addObject(&south_wall);
    scene.addObject(&east_wall);
    scene.addObject(&west_wall);
    scene.addObject(&ceiling);

    scene.addObject(&wrapped_pokemon_table);
    scene.addObject(&wrapped_squirtle);
    scene.addObject(&wrapped_porygon);
    scene.addObject(&wrapped_charmander);
    scene.addObject(&wrapped_bulbasaur);

    scene.addObject(&wrapped_porygon_machine);
    scene.addObject(&wrapped_computer_table);
    scene.addObject(&wrapped_computer);
    scene.addObject(&wrapped_heal_machine);
    scene.addObject(&wrapped_bookshelf);

    scene.addObject(&pokeball_1);
    scene.addObject(&pokeball_2);
    scene.addObject(&pokeball_3);

    scene.addLight(&light);
    scene.addLight(&porygon_machine_light);

    scene.paint(canvas);

    Renderer renderer = Renderer(scene, canvas);
    renderer.start();
    //return scene.render(canvas);
}
