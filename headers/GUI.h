#ifndef _GUI
#define _GUI

#include "../math/vec3.h"
#include <iostream>
#include <string>
#include <unordered_map>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_sdl2.h"

class World;
class GUI {
private:
  World *P_world;
  ImGuiIO *io;

  void overlay();
  void editObject();
  void effects();

  Vector3f rotation;
  Vector3f size;
  Vector3f pos;
  Vector3f velocity;
  Color3f color;
  bool renderObj;
  std::string choosenObj;

public:
  GUI() {}
  ~GUI() {}
  GUI(World *_w);

  void load();
  void update();
  void render() const;
  void clean() const;

  void processevents(SDL_Event &event);
};

#endif
