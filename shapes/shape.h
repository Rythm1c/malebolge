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
      : color(Color3f(1.0)), draw(true), texture(nullptr),
        transform(Transform()), velocity(Vector3f(0.0)),
        inverseMass(0.0), mesh(nullptr) {}

  ~Shape() {}

  void init();
  void render();
  void clean();

  virtual ShapeType getType() const = 0;

  Color3f color;
  bool draw;
  class Texture *texture;

  Transform transform;
  Vector3f pos() { return this->transform.translation; }
  void translate(Vector3f pos) { this->transform.translation = pos; }
  Quat orientation() { return this->transform.orientation; }
  void orient(Quat orientation) { this->transform.orientation = orientation; }

  Vector3f velocity;
  float inverseMass;

  void applyimpulseLinear(const Vector3f &impulse);

protected:
  Mesh *mesh;
};
#endif
