#ifndef SCENE
#define SCENE

#include "../math/mat4.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Shader;
class Engine;
class Object;
class Camera;
// class Framebuffer;

class World {
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
};

#endif
