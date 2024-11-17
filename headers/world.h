#ifndef SCENE
#define SCENE

#include <iostream>
#include "../math/mat4.h"
#include <vector>
#include <map>
#include <string>

class Shader;
class Engine;
class Object;
class Camera;
// class Framebuffer;

class World
{
public:
    World();
    ~World() {}

    void load();
    void update();
    void render();
    void clean();

    bool pause;

    Camera *P_camera;
    class AssetManager *assets;

private:
    Shader *S_obj;
    Shader *S_line;
    Shader *S_quad;

    class Physics *physics;
    class Model *player;
};

#endif