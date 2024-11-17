#include "../headers/engine.h"
#include "../headers/window.h"
#include "../headers/input.h"
#include "../headers/world.h"
#include "../headers/GUI.h"

static auto lastFrameDuration = std::chrono::high_resolution_clock::now();

Engine::Engine()
    : fps(0),
      deltaTime(0),
      running(true),
      P_world(nullptr),
      P_gui(nullptr),
      P_inputhandler(nullptr),
      P_window(nullptr) {}

Engine::~Engine()
{
    P_world->clean();
    P_gui->clean();
    delete this->P_world;
    delete this->P_gui;
    delete this->P_inputhandler;
    delete this->P_window;
}

void Engine::init()
{

    this->P_window = new Window();
    this->P_window->init();

    this->P_world = new World();
    this->P_world->load();

    this->P_gui = new GUI(P_world);
    this->P_gui->load();

    this->P_inputhandler = new InputHandler(P_world);
    this->P_inputhandler->populateKeys();
}
void Engine::calcFps()
{
    auto now = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(now - lastFrameDuration).count();
    lastFrameDuration = now;
    fps = 1.0 / deltaTime;
}
void Engine::mainLoop()
{
    while (this->running)
    {
        this->calcFps();
        this->P_inputhandler->processInput();
        this->P_world->update();
        this->P_gui->update();
        this->P_world->render();
        this->P_gui->render();
        this->P_window->swapBuffer();
    }
}
