#include "../headers/scene.h"
#include <iostream>
#include <chrono>

using namespace std;

Scene::Scene(){
    this->ambient = Vec(0.2, 0.2, 0.2);
}

Scene::Scene(Camera camera, Color background){
    this->camera = camera;
    this->background = background;
    this->ambient = Vec(0.2, 0.2, 0.2);
}

Scene::Scene(Camera camera, Color background, Vec ambient){
    this->camera = camera;
    this->background = background;
    this->ambient = ambient;
}

Scene::Scene(Camera camera, Color background, vector<Object*> objects, vector<Light*> lights){
    this->camera = camera;
    this->background = background;
    this->objects = objects;
    this->lights = lights;
    this->ambient = Vec(0.2, 0.2, 0.2);
}

Scene::Scene(Camera camera, Color background, vector<Object*> objects, vector<Light*> lights, Vec ambient){
    this->camera = camera;
    this->background = background;
    this->objects = objects;
    this->lights = lights;
    this->ambient = ambient;
}

void Scene::addObject(Object* object){
    this->objects.push_back(object);
}

void Scene::addLight(Light* light){
    this->lights.push_back(light);
}

optional<Point> Scene::get_closest_colision(int frame_x, int frame_y){
    int l = camera.n_l - frame_y;
    int c = frame_x;

    Vector diff_y = (camera.j * (camera.delta_y/2)) + ((camera.j * camera.delta_y) * l);
    Vector diff_x = (camera.i * (camera.delta_x/2)) + ((camera.i * camera.delta_x) * c);
    
    Point upper_left = camera.origin - (camera.i * camera.width/2) + camera.j * camera.height/2 + camera.k * camera.d;

    Point p_j = upper_left - diff_x - diff_y;

    Ray ray = Ray(camera.origin, p_j);

    double smallest_root = numeric_limits<double>::infinity();
    LitPoint closest_point;

    for(Object* s : objects){

        optional<LitPoint> intersect = s->colide(ray);
        
        if (intersect.has_value() && intersect.value().t > 0){
            double t = intersect.value().t;

            if(t < smallest_root){
                smallest_root = t;
                closest_point = intersect.value();
            }
        }
    }

    if(smallest_root < numeric_limits<double>::infinity()) return closest_point;
    return nullopt;
}

void Scene::paint(Canvas& canvas){
    
    auto start_time = chrono::high_resolution_clock::now();

    cout << "Calculating intersections..." << endl;

    Point upper_left = camera.origin - (camera.i * camera.width/2) + (camera.j * camera.height/2) + (camera.k * camera.d);

    //cout << "Upper_left: " << upper_left.x << " " << upper_left.y << " " << upper_left.z << endl ;

    for(int l = 0; l < camera.n_l; l++){

        Vector diff_y = (camera.j * (camera.delta_y/2)) + ((camera.j * camera.delta_y) * l);
        
        for(int c = 0; c < camera.n_c; c++){

            Vector diff_x = (camera.i * (camera.delta_x/2)) + ((camera.i * camera.delta_x) * c);

            Point p_j = upper_left + diff_x - diff_y;

            //cout << "p_j: " << p_j.x << " " << p_j.y << " " << p_j.z << endl ;

            Ray ray = Ray(camera.origin, p_j);
            Color cor_atual = background;
            double smallest_root = numeric_limits<double>::infinity();
            LitPoint closest_point;
            bool intersected = false;

            for(long unsigned int i = 0; i < objects.size(); i++){

                optional<LitPoint> intersect = objects[i]->colide(ray);
                
                if (intersect.has_value() && intersect.value().t > 0){
                    LitPoint p = intersect.value();

                    if(p.t < smallest_root){
                        smallest_root = p.t;
                        closest_point = p;
                        intersected = true;
                    }
                }
            }
            if(intersected){

                Vec ambient_intensity = this->ambient * closest_point.material.ambient;
                Vec color_intensity = ambient_intensity;

                for(Light* light : lights){
                    Vec diffuse_specular = light->get_diffuse_and_specular(closest_point, this->objects, ray);
                    color_intensity = color_intensity + diffuse_specular;
                }

                if(color_intensity.x > 1) color_intensity.x = 1;
                if(color_intensity.y > 1) color_intensity.y = 1;
                if(color_intensity.z > 1) color_intensity.z = 1;  

                cor_atual = color_intensity * closest_point.color;
            }
            canvas.matrix[l][c] = cor_atual;
        }
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
    cout << "Done!" << endl;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds" << endl;
}