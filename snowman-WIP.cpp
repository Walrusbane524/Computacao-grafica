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
#include "headers/cylinder.h"
#include "headers/plane.h"
#include "headers/light.h"

using namespace std;

int main(){

    int n_l = 400;
    int n_c = 400;
    double d = 2.5;

    Camera camera = Camera(Point(0, 0, 20), 1, -1, 1, -1, n_l, n_c, d);
    Canvas canvas = Canvas(n_l, n_c);
    Sphere cabeca = Sphere(Point(0,  25, -100), 10, Color(255, 255, 255));
    Sphere tronco = Sphere(Point(0,   5, -100), 15, Color(255, 255, 255));
    Sphere barriga = Sphere(Point(0, -20, -100), 20, Color(255, 255, 255));
    Cylinder braco_direito = Cylinder(Point(14, 8, -100), Vector(0.7, -0.3, 0).normalize(), 1, 15, Color(205, 133, 63));
    Cylinder braco_esquerdo = Cylinder(Point(-14, 8, -100), Vector(-0.7, -0.3, 0).normalize(), 1, 15, Color(205, 133, 63));
    Plane plano = Plane(Point(0, -40, -100), Vector(0, 1, 0), Color(70, 130, 180));

    Cylinder chapeu = Cylinder(Point(0, 32, -100), Vector(0,1,0).normalize(), 12, 0.5, Color(0, 0, 0));
    Cylinder chapeu2 = Cylinder(Point(0, 36.5, -100), Vector(0, 1, 0).normalize(), 9, 4, Color(0, 0, 0));
    Cylinder chapeu3 = Cylinder(Point(0, 34, -100), Vector(0, 1, 0).normalize(), 9.1, 2, Color(255, 255, 255));

    Sphere olho1 = Sphere(Point(2.5,  25, -90), 1, Color(0, 0, 0));
    Sphere olho2 = Sphere(Point(-2.5,  25, -90), 1, Color(0, 0, 0));

    Sphere boca1 = Sphere(Point(-1.94602,  20.6649, -91.2012), 0.5, Color(0, 0, 0));
    Sphere boca2 = Sphere(Point(-1.5756,  20.4828, -91.2187), 0.5, Color(0, 0, 0));
    Sphere boca3 = Sphere(Point(-1.20525,   20.3038, -91.2539), 0.5, Color(0, 0, 0));
    Sphere boca4 = Sphere(Point(-0.648669,  20.2941, -91.2004), 0.5, Color(0, 0, 0));
    Sphere boca5 = Sphere(Point(-0.0926492,   20.2902, -91.1791), 0.5, Color(0, 0, 0));
    Sphere boca6 = Sphere(Point(0.0926492,   20.2902, -91.1791), 0.5, Color(0, 0, 0));
    Sphere boca7 = Sphere(Point(0.648669,  20.2941, -91.2004), 0.5, Color(0, 0, 0));
    Sphere boca8 = Sphere(Point(1.20525,   20.3038, -91.2539), 0.5, Color(0, 0, 0));
    Sphere boca9 = Sphere(Point(1.5756,  20.4828, -91.2187), 0.5, Color(0, 0, 0));
    Sphere boca10 = Sphere(Point(1.94602,  20.6649, -91.2012), 0.5, Color(0, 0, 0));

    //Light light(Point(0, 0, 20), 1.0, 1.0, 1.0);
    Light light(Point(0, 100, -80), 1, 1, 1);

    Color background = Color(100, 100, 100);

    Scene scene = Scene(camera, background, Vec(0.8, 0.8, 0.8));

    Sphere botao1 = Sphere(Point(0.106044, 10.4984, -86.0445), 1, Color(0, 0, 0));
    Sphere botao2 = Sphere(Point(0.10401, 5.0965, -84.0101), 1, Color(0, 0, 0));
    Sphere botao3 = Sphere(Point(0.0990099, -0.0990099, -79.0099), 1, Color(0, 0, 0));

    scene.addObject(&cabeca);
    scene.addObject(&olho1);
    scene.addObject(&olho2);
    scene.addObject(&olho2);

    scene.addObject(&boca1);
    scene.addObject(&boca2);
    scene.addObject(&boca3);
    scene.addObject(&boca4);
    scene.addObject(&boca5);
    scene.addObject(&boca6);
    scene.addObject(&boca7);
    scene.addObject(&boca8);
    scene.addObject(&boca9);
    scene.addObject(&boca10);

    scene.addObject(&tronco);
    scene.addObject(&barriga);
    scene.addObject(&botao1);
    scene.addObject(&botao2);
    scene.addObject(&botao3);
    scene.addObject(&braco_direito);
    scene.addObject(&braco_esquerdo);
    scene.addObject(&plano);
    scene.addObject(&chapeu);
    scene.addObject(&chapeu2);
    scene.addObject(&chapeu3);

    scene.addLight(&light);

    optional<Point> ponto_ = scene.get_closest_colision(400, 400);

    if(ponto_.has_value()){
        cout << ponto_.value().x << endl;
        cout << ponto_.value().y << endl;
        cout << ponto_.value().z << endl;
        Sphere ponto_real = Sphere(Point(ponto_.value().x,  ponto_.value().y, ponto_.value().z), 1, Color(0, 255, 0));
        
        scene.addObject(&ponto_real);
    }

    scene.paint(canvas);

    return canvas.render();
}
