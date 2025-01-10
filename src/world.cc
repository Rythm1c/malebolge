
#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <map>
#include <string>

#include "../headers/GUI.h"
#include "../headers/camera.h"
#include "../headers/engine.h"
#include "../headers/window.h"
#include "../headers/world.h"
#include "../math/math.h"
#include "../physics/physics.h"
#include "../physics/shapes.h"
#include "../render/render.h"
#include "../render/primitives.h"

Mat4x4 view = Mat4x4();
Mat4x4 projection = Mat4x4();
Vector3f lightdir = Vector3f(0.0);

World::World()
    : pause(false), P_camera(new Camera()), S_line(nullptr), S_obj(nullptr),
      S_quad(nullptr) {}

void World::clean()
{
  S_obj->clean();
  delete S_obj;
  S_line->clean();
  delete S_line;
  S_quad->clean();
  delete S_quad;

  for (auto &body : this->bodies)
  {
    body->clean();
    delete body;
  }

  delete P_camera;
}

void World::load()
{
  S_obj = new Shader("shaders/shader.vs", "shaders/shader.fs");
  S_line = new Shader("shaders/line.vert", "shaders/line.frag");
  S_quad = new Shader("shaders/effects.vert", "shaders/effects.frag");

  lightdir = Vector3f(-0.2, -1.0, 0.3);

  this->bodies.push_back(new Body());
  this->bodies[0]->setShape(new Sphere(1.0));
  *this->bodies[0]->mesh = UVSphere(60, 60, Color3f(0.6));
  this->bodies[0]->translate({-3.0, 16.0, 7.0});
  this->bodies[0]->inverseMass = 1.0;

  this->bodies.push_back(new Body());
  this->bodies[1]->setShape(new Sphere(2.0));
  *this->bodies[1]->mesh = UVSphere(60, 60, WHITE);
  this->bodies[1]->translate({2.0, 16.0, 30.0});
  this->bodies[1]->inverseMass = 1.0;
  this->bodies[1]->elasticity = 0.6;
  this->bodies[1]->texture = createCheckeredTexture(500, 500, WHITE, Color3f(0.2), 20);

  Color3f cols[6] = {GREEN, CYAN, BLUE, YELLOW, RED, PURPLE};
  this->bodies.push_back(new Body());
  this->bodies[2]->setShape(new Sphere(1.0));
  *this->bodies[2]->mesh = CubeSpere(60, cols);
  this->bodies[2]->translate({-3.0, 16.0, 15.0});
  this->bodies[2]->inverseMass = 1.0;
  // this->bodies[2]->texture = createCheckeredTexture(500, 500, Color3f(0.71, 1.0, 0.44), Color3f(0.2), 4);

  Color3f cols2[6] = {WHITE, WHITE, ORANGE, ORANGE, RED, RED};
  this->bodies.push_back(new Body());
  this->bodies[3]->setShape(new Sphere(2.0));
  *this->bodies[3]->mesh = CubeSpere(60, cols2);
  this->bodies[3]->translate({3.0, 16.0, 20.0});
  this->bodies[3]->elasticity = 0.75;
  this->bodies[3]->inverseMass = 1.0;

  this->bodies.push_back(new Body());
  this->bodies[4]->setShape(new Sphere(1000.0));
  *this->bodies[4]->mesh = CubeSpere(60, cols2);
  this->bodies[4]->translate({0.0, -1000.0, 0.0});
  this->bodies[4]->inverseMass = 0.0;
  this->bodies[4]->elasticity = 1.0;
  this->bodies[4]->texture = createCheckeredTexture(2000, 2000, WHITE, Color3f(0.2), 50);

  Color3f cols3[6] = {WHITE, WHITE, PINK, PINK, BLUE, BLUE};
  this->bodies.push_back(new Body());
  this->bodies[5]->setShape(new Sphere(1.5));
  *this->bodies[5]->mesh = CubeSpere(50, cols3);
  this->bodies[5]->translate({-5.0, 16.0, 20.0});
  this->bodies[5]->inverseMass = 1.0;
  // this->shapes[5]->texture = createGridTexture(500, 500, WHITE, Color3f(0.2), 20, 20);
}
void World::update()
{
  float deltaTime = Engine::getInstance()->deltaTime;
  // impliment pause futionality in gui
  if (!pause)
  {

    for (int i = 0; i < this->bodies.size(); i++)
    {
      for (int j = this->bodies.size() - 1; j != i; j--)
      {

        if (intersect(this->bodies[i], this->bodies[j]))
        {
          resolveIntersection(this->bodies[i], this->bodies[j]);
        }
      }
    }

    for (auto &body : this->bodies)
    {
      if (body->inverseMass != 0.0)
      {
        // I = dp , F = dp / dt => dp = F * dt => I = F * dt
        // F = mgs
        float mass = 1.0 / body->inverseMass;
        Vector3f impulse = GRAVITY * mass * deltaTime;
        body->applyimpulseLinear(impulse);
      }
    }

    for (auto &body : this->bodies)
    {
      Vector3f pos = body->pos();
      Vector3f velocity = body->velocity * deltaTime;
      body->translate(pos + velocity);
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

  for (auto &body : this->bodies)
  {
    if (body->draw)
    {
      bool textured = body->texture != nullptr;
      S_obj->updateInt("textured", textured);
      if (textured)
      {
        glBindTexture(GL_TEXTURE_2D, body->texture->id);
      }

      S_obj->updateMat4("transform", body->transform.get());
      body->render();
    }
  }
}
