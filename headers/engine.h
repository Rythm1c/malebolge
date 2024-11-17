#ifndef _ENGINE
#define _ENGINE

#include <iostream>
#include <chrono>

class Engine
{
public:
    ~Engine();
    Engine(const Engine &obj) = delete;

    static Engine *getInstance()
    {
        return instancePtr;
    }

    void run()
    {
        init();
        mainLoop();
    }

    class World *P_world;
    class GUI *P_gui;
    class InputHandler *P_inputhandler;
    class Window *P_window;

    float deltaTime;
    float fps;
    bool running;

private:
    Engine();
    static Engine *instancePtr;

    void init();
    void mainLoop();
    void calcFps();
};
#endif