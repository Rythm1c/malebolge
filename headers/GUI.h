#ifndef _GUI
#define _GUI

#include <iostream>
#include <string>
#include <unordered_map>
#include "../math/vec3.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl2.h"
#include "../imgui/imgui_impl_opengl3.h"

class World;
class GUI
{
private:
    World *P_world;
    ImGuiIO *io;

    void overlay();
    void editObject();
    void effects();

    v3D rotation;
    v3D size;
    v3D pos;
    v3D velocity;
    color3f color;
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