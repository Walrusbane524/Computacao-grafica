#include "../headers/spherical_wrapper.h"
#include <limits>
#include <iostream>
#include <algorithm>

SphericalWrapper::SphericalWrapper(){
    this->sphere = Sphere();
}

SphericalWrapper::SphericalWrapper(ObjMesh* mesh, int depth){

    this->mesh = mesh;

    double sum_x = 0.0;
    double sum_y = 0.0;
    double sum_z = 0.0;

    for(Triangle face : mesh->triangles){
        sum_x += face.p1.x;
        sum_y += face.p1.y;
        sum_z += face.p1.z;
        
        sum_x += face.p2.x;
        sum_y += face.p2.y;
        sum_z += face.p2.z;
        
        sum_x += face.p3.x;
        sum_y += face.p3.y;
        sum_z += face.p3.z;
    }
    
    int triangle_total = mesh->triangles.size() * 3;

    double avg_x = sum_x/triangle_total;
    double avg_y = sum_y/triangle_total;
    double avg_z = sum_z/triangle_total;

    Point mesh_center = Point(avg_x, avg_y, avg_z);

    double largest_distance = -std::numeric_limits<double>::infinity();

    for(Triangle triangle : mesh->triangles){
        double distance_p1 = (triangle.p1 - mesh_center).magnitude();
        double distance_p2 = (triangle.p2 - mesh_center).magnitude();
        double distance_p3 = (triangle.p3 - mesh_center).magnitude();

        if(distance_p1 > largest_distance)
            largest_distance = distance_p1;
        if(distance_p2 > largest_distance)
            largest_distance = distance_p2;
        if(distance_p3 > largest_distance)
            largest_distance = distance_p3;
    }

    this->sphere = Sphere(mesh_center, largest_distance + 0.01 * largest_distance);

    if (depth != 0 && mesh->triangles.size() > 2){

        ObjMesh sorted_mesh = *mesh;

        //sort(sorted_mesh.triangles.begin(), sorted_mesh.triangles.end(), compareTriangles);

        size_t middleIndex = sorted_mesh.triangles.size() / 2;
        //cout << "mesh.triangles.size(): " << mesh.triangles.size() << endl;
        //cout << "middleIndex: " << middleIndex << endl;
        
        vector<Triangle> sub_vector1(sorted_mesh.triangles.begin(), sorted_mesh.triangles.begin() + middleIndex);
        vector<Triangle> sub_vector2(sorted_mesh.triangles.begin() + middleIndex, sorted_mesh.triangles.end());

        if(mesh->normals.empty()){
            this->objects.push_back(new SphericalWrapper(new ObjMesh(sorted_mesh.points, sorted_mesh.faces, sub_vector1, sorted_mesh.uv_points, sorted_mesh.texture), depth - 1));
            this->objects.push_back(new SphericalWrapper(new ObjMesh(sorted_mesh.points, sorted_mesh.faces, sub_vector2, sorted_mesh.uv_points, sorted_mesh.texture), depth - 1));
        }
        else{
            this->objects.push_back(new SphericalWrapper(new ObjMesh(sorted_mesh.points, sorted_mesh.faces, sub_vector1, mesh->uv_points, sorted_mesh.normals, sorted_mesh.texture), depth - 1));
            this->objects.push_back(new SphericalWrapper(new ObjMesh(sorted_mesh.points, sorted_mesh.faces, sub_vector2, mesh->uv_points, sorted_mesh.normals, sorted_mesh.texture), depth - 1));
        }
    }
    else
        this->objects.push_back(mesh);
}

SphericalWrapper::SphericalWrapper(Sphere sphere, vector<Object*> objects){
    this->sphere = sphere;
    this->objects = objects;
}

optional<LitPoint> SphericalWrapper::colide(Ray ray) const {
    optional<LitPoint> boundary_intersect = this->sphere.colide(ray);

    if (boundary_intersect.has_value() && boundary_intersect.value().t > 0) {
        //cout << "Intersected boundary" << endl;
        double smallest_distance = numeric_limits<double>::infinity();
        LitPoint closest_point;
        bool intersected = false;

        for (Object* object : this->objects) {
            optional<LitPoint> intersect = object->colide(ray);

            if (intersect.has_value() && intersect.value().t > 0) {
                if (intersect.value().t < smallest_distance) {
                    //cout << "Intersected sub_object" << endl;
                    smallest_distance = intersect.value().t;
                    closest_point = intersect.value();
                    intersected = true;
                }
            }
        }

        if (intersected) {
            //cout << "closest_point.color.r = " << closest_point.color.r << endl;
            //cout << "closest_point.color.g = " << closest_point.color.g << endl;
            //cout << "closest_point.color.b = " << closest_point.color.b << endl;
            return closest_point;
        }
    }

    return nullopt;
}

bool SphericalWrapper::compareTriangles(const Triangle& a, const Triangle& b){
    Point centerA = averagePoint(a);
    Point centerB = averagePoint(b);

    // Lexicographical comparison (ascending order)
    if (centerA.x != centerB.x) {
        return centerA.x < centerB.x;
    } else if (centerA.y != centerB.y) {
        return centerA.y < centerB.y;
    } else {
        return centerA.z < centerB.z;
    }
}

Point SphericalWrapper::averagePoint(const Triangle& triangle){
    double avgX = (triangle.p1.x + triangle.p2.x + triangle.p3.x) / 3.0;
    double avgY = (triangle.p1.y + triangle.p2.y + triangle.p3.y) / 3.0;
    double avgZ = (triangle.p1.z + triangle.p2.z + triangle.p3.z) / 3.0;
    return Point(avgX, avgY, avgZ);
}

void SphericalWrapper::info(){
    cout << "Spherical Wrapper = {" << endl;
    sphere.info();
    mesh->info();
    cout << "}" << endl;
}