#include "../headers/window.h"

Window::Window() : win(nullptr), context(nullptr), area(iv2D(0)) {}
void Window::swapBuffer() { SDL_GL_SwapWindow(this->win); }
Window::~Window() {
  SDL_GL_DeleteContext(this->context);
  SDL_DestroyWindow(this->win);
  SDL_Quit();
}
void Window::reSize() {
  SDL_GetWindowSize(this->win, &this->area.x, &this->area.y);
  glViewport(0, 0, this->area.x, this->area.y);
}
void Window::init() {

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::runtime_error("failed to create SDL window!");
  }
  // window creation
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  this->area.x = 800;
  this->area.y = 600;
  int flags =
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
  this->win = SDL_CreateWindow("little-engine", 100, 100, this->area.x,
                               this->area.y, flags);
  this->context = SDL_GL_CreateContext(this->win);

  if (SDL_GL_MakeCurrent(this->win, this->context) != 0) {
    std::runtime_error("failed to set an opengl context with window!");
  }

  SDL_GL_SetSwapInterval(1);

  glewExperimental = true;
  glewInit();

  glViewport(0, 0, this->area.x, this->area.y);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.2, 0.2, 0.2, 1.0);
}
