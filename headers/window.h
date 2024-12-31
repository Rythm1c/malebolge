#ifndef LRE_WINDOW
#define LRE_WINDOW

#include <iostream>

#include <GL/glew.h>

#include <GL/gl.h>

#include "../math/vec2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Window {
public:
  Window();
  ~Window();
  SDL_Window *win;
  SDL_GLContext context;
  Vector2i area;

  void init();
  void swapBuffer();
  void reSize();
  float ratio() { return (float)area.x / (float)area.y; }
};

#endif
