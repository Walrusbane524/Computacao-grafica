#include "../headers/scene.h"

using namespace std;

Scene::Scene(){}

Scene::Scene(Camera camera, Color background){
    this->camera = camera;
    this->background = background;
}

Scene::Scene(Camera camera, Color background, vector<Object*> objects){
    this->camera = camera;
    this->background = background;
    this->objects = objects;
}

void Scene::addObject(Object* object){
    this->objects.push_back(object);
}

void Scene::paint(Canvas& canvas){

    for(int l = 0; l < camera.n_l; l++){
        double y_l = camera.j_ymax - (camera.delta_y/2.0) - (l*camera.delta_y);
        
        for(int c = 0; c < camera.n_c; c++){

            double x_c = camera.j_xmin + (camera.delta_x/2.0) + (c*camera.delta_x);
            Point p_j = Point(x_c, y_l, camera.origin.z - camera.d);
            Ray ray = Ray(camera.origin, p_j);
            Color cor_atual = background;
            double smallest_root = numeric_limits<double>::infinity();

            for(Object* s : objects){
                optional<double> intersect = s->colide(ray);
                if (intersect.has_value()){
                    double root = intersect.value();
                    if(root < smallest_root){
                        root = smallest_root;
                        cor_atual = s->color;
                    }
                }
            }
            canvas.matrix[l][c] = cor_atual;
        }
    }
}