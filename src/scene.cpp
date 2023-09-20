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
                for(Light* light : lights){
                    
                    Ray light_ray = Ray(light->point, (Point)closest_point);
                    double distance_from_light = (light->point - closest_point).magnitude();
                    double light_intersect = false;

                    // Check if there is another object between the light and the object
                    for(Object* o : objects){

                        optional<LitPoint> intersect = o->colide(light_ray);
                        
                        if (intersect.has_value() && distance_from_light - intersect.value().t > 0.001){
                            light_intersect = true;
                            break;
                        }
                    }

                    Vec color_intensity = this->ambient;

                    if(!light_intersect){
                        Vector l_ = (light->point - closest_point).normalize();
                        Vector v = Vector(-ray.direction.x, -ray.direction.y, -ray.direction.z);
                        Vector r = (closest_point.normal * l_.dot(closest_point.normal) * 2) - l_;

                        double f_dif = l_.dot(closest_point.normal);
                        double f_spec = v.dot(r);

                        if (f_dif < 0) f_dif = 0;
                        if (f_spec < 0) f_spec = 0;

                        Vec diffuse_intensity = *light * (closest_point.roughness * f_dif);
                        Vec specular_intensity = *light * (closest_point.shine * f_spec);

                        color_intensity = this->ambient + diffuse_intensity + specular_intensity;
                    }

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