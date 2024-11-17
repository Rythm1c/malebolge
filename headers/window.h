#ifndef LRE_WINDOW
#define LRE_WINDOW

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "../math/vec2.h"

class Window
{
public:
    Window();
    ~Window();
    SDL_Window *win;
    SDL_GLContext context;
    iv2D area;

    void init();
    void swapBuffer();
    void reSize();
    float ratio() { return (float)area.x / (float)area.y; }
};

#endif