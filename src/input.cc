#include "../headers/input.h"
#include "../headers/engine.h"
#include "../headers/window.h"
#include "../headers/world.h"
// #include "../headers/GUI.h"
#include "../headers/camera.h"

InputHandler::InputHandler(World *_w) : P_world(_w), keyboardState(nullptr) {}
void InputHandler::populateKeys()
{
  int nkeys;
  this->keyboardState = SDL_GetKeyboardState(&nkeys);
}
void InputHandler::processInput(float delta)
{

  this->specialKeys();
  this->keyboard(delta);
}

void InputHandler::specialKeys()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    // Engine::getInstance()->P_gui->processevents(event);
    switch (event.type)
    {
    case SDL_QUIT:
      Engine::getInstance()->running = false;
      break;

    case SDL_KEYDOWN:
      // handle special key stokes
      switch (event.key.keysym.sym)
      {
      case SDLK_m:
        break;
      default:
        break;
      }
      break;

    case SDL_KEYUP:
      break;

    case SDL_MOUSEMOTION:
      if (event.button.button == SDL_BUTTON_LEFT)
      {
        this->P_world->P_camera->rotation(
            iv2D(event.motion.xrel, event.motion.yrel));
      }
      break;

    case SDL_WINDOWEVENT:
      switch (event.window.event)
      {
      case SDL_WINDOWEVENT_SIZE_CHANGED:
        Engine::getInstance()->P_window->reSize();
        break;
      default:
        break;
      }
      break;

    default:
      break;
    }
  }
}
void InputHandler::keyboard(float delta)
{

  if (this->keyboardState[SDL_SCANCODE_W])
  {
    this->P_world->P_camera->moveForwards(delta);
  }
  if (this->keyboardState[SDL_SCANCODE_S])
  {
    this->P_world->P_camera->moveBackwards(delta);
  }
  if (this->keyboardState[SDL_SCANCODE_D])
  {
    this->P_world->P_camera->moveRight(delta);
  }
  if (this->keyboardState[SDL_SCANCODE_A])
  {
    this->P_world->P_camera->moveLeft(delta);
  }
  // for zooming in and out
  if (this->keyboardState[SDL_SCANCODE_Z])
  {
    this->P_world->P_camera->fov++;
  }
  else if (this->keyboardState[SDL_SCANCODE_X])
  {
    this->P_world->P_camera->fov--;
  }
}
