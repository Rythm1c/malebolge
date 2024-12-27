#ifndef _ENGINE
#define _ENGINE

#include <chrono>
#include <iostream>

class Engine {
public:
  ~Engine();
  Engine(const Engine &obj) = delete;

  static Engine *getInstance() { return instancePtr; }

  void run() {
    init();
    mainLoop();
  }

  float fps;
  float deltaTime;
  bool running;

  class World *P_world;
  class GUI *P_gui;
  class InputHandler *P_inputhandler;
  class Window *P_window;

private:
  Engine();
  static Engine *instancePtr;

  void init();
  void mainLoop();
  void calcFps();
};
#endif
