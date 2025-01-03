#ifndef SHAPE_H
#define SHAPE_H

#include "../math/transform.h"
#include "../math/vec3.h"
#include <iostream>
#include <vector>

enum ShapeType
{
  SHAPE_SPHERE,
  SHAPE_CUBE
};

struct Mesh;

class Shape
{

public:
  Shape()
      : draw(true), texture(nullptr), transform(Transform()),
        velocity(Vector3f(0.0)), inverseMass(0.0), mesh(nullptr) {}

  ~Shape() {}

  void init();
  void render();
  void clean();

  virtual ShapeType getType() const = 0;

  bool draw;
  class Texture *texture;

  Transform transform;

  Vector3f pos() { return this->transform.translation; }
  Quat orientation() { return this->transform.orientation; }

  void translate(Vector3f pos) { this->transform.translation = pos; }
  void orient(Quat orientation) { this->transform.orientation = orientation; }

  Vector3f velocity;
  float inverseMass;

  void applyimpulseLinear(const Vector3f &impulse);

  Mesh *mesh;
};
#endif
