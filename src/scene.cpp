#include "../headers/scene.h"
#include <iostream>

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
    double y_l = camera.j_ymax - (camera.delta_y/2.0) - (l*camera.delta_y);
    double x_c = camera.j_xmin + (camera.delta_x/2.0) + (c*camera.delta_x);
    Point p_j = Point(x_c, y_l, camera.origin.z - camera.d);

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
    
    for(int l = 0; l < camera.n_l; l++){
        double y_l = camera.j_ymax - (camera.delta_y/2.0) - (l*camera.delta_y);
        
        for(int c = 0; c < camera.n_c; c++){
            double x_c = camera.j_xmin + (camera.delta_x/2.0) + (c*camera.delta_x);

            Point p_j = Point(x_c, y_l, camera.origin.z - camera.d);
            Ray ray = Ray(camera.origin, p_j);
            Color cor_atual = background;
            double smallest_root = numeric_limits<double>::infinity();
            LitPoint closest_point;
            bool intersected = false;

            for(Object* s : objects){

                optional<LitPoint> intersect = s->colide(ray);
                
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
                for(Light* light : lights){
                    Vector l_ = (light->point - closest_point).normalize();
                    Vector v = Vector(-ray.direction.x, -ray.direction.y, -ray.direction.z);
                    Vector r = (closest_point.normal * l_.dot(closest_point.normal) * 2) - l_;

                    double f_dif = l_.dot(closest_point.normal);
                    double f_spec = v.dot(r);

                    if (f_dif < 0) f_dif = 0;
                    if (f_spec < 0) f_spec = 0;

                    Vec diffuse_intensity = *light * (closest_point.roughness * f_dif);
                    Vec specular_intensity = *light * (closest_point.shine * f_spec);

                    Vec color_intensity = this->ambient + diffuse_intensity + specular_intensity;

                    if(color_intensity.x > 1) color_intensity.x = 1;
                    if(color_intensity.y > 1) color_intensity.y = 1;
                    if(color_intensity.z > 1) color_intensity.z = 1;

                    cor_atual = color_intensity * closest_point.color;
                }   
            }
            // if(l == 90) cor_atual = Color(255,0,0);
            canvas.matrix[l][c] = cor_atual;
        }
    }
}