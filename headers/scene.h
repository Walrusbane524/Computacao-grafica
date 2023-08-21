#include <vector>

#include "../headers/object.h"
#include "../headers/canvas.h"
#include "../headers/camera.h"

using namespace std;

class Scene{

    public:
    Camera camera;
    Color background;
    vector<Object*> objects;

    Scene();

    Scene(Camera camera, Color background);

    Scene(Camera camera, Color background, vector<Object*> objects);

    void addObject(Object* object);

    void paint(Canvas& canvas);
};