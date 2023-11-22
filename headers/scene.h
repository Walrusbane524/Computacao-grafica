#include <vector>
#include <optional>
#include <SDL2/SDL.h>

#include "../headers/object.h"
#include "../headers/canvas.h"
#include "../headers/camera.h"
#include "../headers/light.h"

using namespace std;

class Scene{

    public:
    Camera camera;
    Color background;
    Vec ambient;
    vector<Object*> objects;
    vector<Light*> lights;
    bool is_running;
    bool is_rendering;

    Scene();

    Scene(Camera camera, Color background);

    Scene(Camera camera, Color background, Vec ambient);

    Scene(Camera camera, Color background, vector<Object*> objects, vector<Light*> lights);

    Scene(Camera camera, Color background, vector<Object*> objects, vector<Light*> lights, Vec ambient);

    optional<LitPoint> get_closest_colision(int frame_x, int frame_y);

    void addObject(Object* object);

    void addLight(Light* light);

    void paint(Canvas& canvas);

    void handleInput(SDL_Event& event, Canvas& canvas);

    void renderFrame(Canvas& canvas, SDL_Renderer* renderer);

    int render(Canvas& canvas);
};