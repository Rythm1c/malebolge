#ifndef LRE_WINDOW
#define LRE_WINDOW

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Window
{
public:
  Window();
  ~Window();
  SDL_Window *win;
  SDL_GLContext context;
  int width;
  int height;

  void init();
  void swapBuffer();
  void reSize();
  float ratio();
};

#endif
