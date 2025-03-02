#ifndef SCENE_H
#define SCENE_H

#include <vector>

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
  std::vector<class Body *> bodies;

private:
  Shader *S_obj;
  Shader *S_line;
  Shader *S_quad;
};

#endif
