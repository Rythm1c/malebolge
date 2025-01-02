
#include <GL/glew.h>

#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <map>
#include <string>

#include "../headers/GUI.h"
#include "../headers/assets.h"
#include "../headers/camera.h"
#include "../headers/engine.h"
#include "../headers/window.h"
#include "../headers/world.h"
#include "../math/math.h"
#include "../physics/physics.h"
#include "../shapes/shape.h"
#include "../shapes/sphere.h"
#include "../shapes/cube.h"
#include "../render/render.h"

mat4x4 view = mat4x4();
mat4x4 projection = mat4x4();
Vector3f lightdir = Vector3f(0.0);

World::World()
    : pause(false), P_camera(nullptr), S_line(nullptr), S_obj(nullptr),
      S_quad(nullptr) {}

void World::clean()
{
  S_obj->clean();
  delete S_obj;
  S_line->clean();
  delete S_line;
  S_quad->clean();
  delete S_quad;

  for (auto &shape : this->shapes)
  {
    shape->clean();
    delete shape;
  }

  delete P_camera;
}

void World::load()
{
  S_obj = new Shader("shaders/shader.vert", "shaders/shader.frag");
  S_line = new Shader("shaders/line.vert", "shaders/line.frag");
  S_quad = new Shader("shaders/effects.vert", "shaders/effects.frag");

  lightdir = Vector3f(-0.2, -1.0, 0.3);

  this->shapes.push_back(new Sphere(0.6, 60, 60, Color3f(0.4)));
  this->shapes[0]->translate({-5.0, 16.0, 12.0});
  this->shapes[0]->inverseMass = 1.0;

  this->shapes.push_back(new Sphere(1.0, 60, 60, Color3f(1.0)));
  this->shapes[1]->translate({2.0, 16.0, 30.0});
  this->shapes[1]->inverseMass = 1.0;
  this->shapes[1]->texture = createCheckeredTexture(500, 500, Color3f(1.0), Color3f(0.2), 20);

  this->shapes.push_back(new Cube(Color3f(0.71, 1.0, 0.44), Vector3f(2.0)));
  this->shapes[2]->translate({-5.0, 16.0, 25.0});
  this->shapes[2]->inverseMass = 1.0;
  this->shapes[2]->texture = createCheckeredTexture(500, 500, Color3f(0.71, 1.0, 0.44), Color3f(0.2), 4);

  this->shapes.push_back(new Cube(Color3f(1.0, 0.58, 0.1), Vector3f(3.0)));
  this->shapes[3]->translate({6.0, 16.0, 20.0});
  this->shapes[3]->inverseMass = 1.0;

  this->shapes.push_back(new Cube(Color3f(1.0), Vector3f(200.0, 2.0, 200.0)));
  this->shapes[4]->translate({0.0, -2.0, 0.0});
  this->shapes[4]->inverseMass = 0.0;
  this->shapes[4]->texture = createGridTexture(2000, 2000, Color3f(1.0), Color3f(0.2), 80, 80);

  std::cout << "break\n";

  for (auto &shape : this->shapes)
  {
    shape->init();
  }

  P_camera = new Camera();
}
void World::update()
{
  float deltaTime = Engine::getInstance()->deltaTime;
  // impliment pause futionality in gui
  if (!pause)
  {

    for (int i = 0; i < this->shapes.size(); i++)
    {
      for (int j = this->shapes.size() - 1; j != i; j--)
      {

        if (intersect(this->shapes[i], this->shapes[j]))
        {
          resolveIntersection(this->shapes[i], this->shapes[j]);
        }
      }
    }

    for (auto &shape : this->shapes)
    {
      if (shape->inverseMass != 0.0)
      {
        // I = dp , F = dp / dt => dp = F * dt => I = F * dt
        // F = mgs
        float mass = 1.0 / shape->inverseMass;
        Vector3f impulse = GRAVITY * mass * deltaTime;
        shape->applyimpulseLinear(impulse);
      }
    }

    for (auto &shape : this->shapes)
    {
      Vector3f pos = shape->pos();
      Vector3f velocity = shape->velocity * deltaTime;
      shape->translate(pos + velocity);
    }
  }

  view = P_camera->view();
  projection = P_camera->projection(Engine::getInstance()->P_window->ratio());
}

void World::render()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  S_obj->use();
  S_obj->updateVec3("L_direction", lightdir);
  S_obj->updateVec3("viewPos", P_camera->pos);
  S_obj->updateMat4("view", view);
  S_obj->updateMat4("projection", projection);

  for (auto &shape : this->shapes)
  {
    if (shape->draw)
    {
      mat4x4 transform = shape->transform.get();
      bool textured = shape->texture != nullptr;
      S_obj->updateInt("textured", textured);
      if (textured)
      {
        glBindTexture(GL_TEXTURE_2D, shape->texture->id);
      }

      S_obj->updateMat4("transform", transform);
      S_obj->updateVec3("col", shape->color);
      shape->render();
    }
  }
}
