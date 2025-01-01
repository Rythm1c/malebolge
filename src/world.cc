
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
  assets->cleanUp();
  delete assets;

  delete P_camera;
}

void World::load()
{
  S_obj = new Shader("shaders/shader.vert", "shaders/shader.frag");
  S_line = new Shader("shaders/line.vert", "shaders/line.frag");
  S_quad = new Shader("shaders/effects.vert", "shaders/effects.frag");

  lightdir = Vector3f(-0.2, -1.0, 0.3);

  assets = new AssetManager();

  assets->addSphere("ball1", 0.6, 60, 60, Color3f(0.4));
  assets->getShape("ball1")->translate({-5.0, 16.0, 12.0});
  assets->getShape("ball1")->draw = true;
  assets->getShape("ball1")->inverseMass = 1.0;

  assets->addSphere("ball2", 1.0, 60, 60, Color3f(1.0));
  assets->getShape("ball2")->translate({2.0, 16.0, 30.0});
  assets->getShape("ball2")->draw = true;
  assets->getShape("ball2")->inverseMass = 1.0;
  assets->getShape("ball2")->texture = createCheckeredTexture(500, 500, Color3f(1.0), Color3f(0.2), 20);

  assets->addCube("cube1", Color3f(0.71, 1.0, 0.44), Vector3f(2.0));
  assets->getShape("cube1")->translate({-5.0, 16.0, 25.0});
  assets->getShape("cube1")->draw = true;
  assets->getShape("cube1")->inverseMass = 1.0;
  assets->getShape("cube1")->texture = createCheckeredTexture(500, 500, Color3f(0.71, 1.0, 0.44), Color3f(0.2), 4);

  assets->addCube("cube2", Color3f(1.0, 0.58, 0.1), Vector3f(3.0));
  assets->getShape("cube2")->translate({6.0, 16.0, 20.0});
  assets->getShape("cube2")->draw = true;
  assets->getShape("cube2")->inverseMass = 1.0;

  /*assets->addTorus("torus", 40, Color3f(0.3, 0.88, 0.2));
  assets->getShape("torus")->transform.scaling = Vector3f(10.0);
  assets->getShape("torus")->transform.translation = {-25.0, 10.0, 30.0};
  assets->getShape("torus")->draw = true;
  assets->getShape("torus")->subDivide = false;
  assets->getShape("torus")->lines = 0.0;*/

  assets->addCube("platform", Color3f(1.0), Vector3f(700.0, 2.0, 700.0));
  assets->getShape("platform")->transform.translation = {0.0, -2.0, 0.0};
  assets->getShape("platform")->inverseMass = 0.0;
  assets->getShape("platform")->texture = createGridTexture(2000, 2000, Color3f(1.0), Color3f(0.2), 60, 60);

  assets->refreshShapeList();

  for (auto &shape : assets->shapes)
  {
    shape.second->init();
  }

  P_camera = new Camera();
}
void World::update()
{
  float deltaTime = Engine::getInstance()->deltaTime;
  if (!pause)
  {

    for (std::map<std::string, Shape *>::iterator iter1 =
             assets->shapes.begin();
         iter1 != assets->shapes.end(); iter1++)
    {
      for (std::map<std::string, Shape *>::reverse_iterator iter2 =
               assets->shapes.rbegin();
           iter2->first != iter1->first; iter2++)
      {

        if (intersect(iter1->second, iter2->second))
        {
          resolveIntersection(iter1->second, iter2->second);
        }
      }
    }
    for (auto &shape : assets->shapes)
    {
      if (shape.second->inverseMass != 0.0)
      {
        // I = dp , F = dp / dt => dp = F * dt => I = F * dt
        // F = mgs
        float mass = 1.0 / shape.second->inverseMass;
        Vector3f impulse = GRAVITY * mass * deltaTime;
        shape.second->applyimpulseLinear(impulse);
      }
    }

    for (auto &shape : assets->shapes)
    {
      Vector3f pos = shape.second->pos();
      Vector3f velocity = shape.second->velocity * deltaTime;
      shape.second->translate(pos + velocity);
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

  for (auto &shape : assets->shapes)
  {
    if (shape.second->draw)
    {
      mat4x4 transform = shape.second->transform.get();
      bool textured = shape.second->texture != nullptr;
      S_obj->updateInt("textured", textured);
      if (textured)
        glBindTexture(GL_TEXTURE_2D, shape.second->texture->id);

      S_obj->updateMat4("transform", transform);
      S_obj->updateVec3("col", shape.second->color);
      shape.second->render();
    }
  }
}
