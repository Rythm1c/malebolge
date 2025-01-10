#ifndef BODY_H
#define BODY_H

#include "../math/transform.h"
#include "../math/vec3.h"

class Body
{
public:
  Body();
  ~Body() {}

  void render();
  void clean();

  bool draw;
  class Texture *texture;

  Transform transform;

  Vector3f pos() { return this->transform.translation; }
  Quat orientation() { return this->transform.orientation; }

  void translate(Vector3f pos) { this->transform.translation = pos; }
  void orient(Quat orientation) { this->transform.orientation = orientation; }

  Vector3f velocity;
  float inverseMass;
  float elasticity;

  void applyimpulseLinear(const Vector3f &impulse);

  class Shape *shape;
  void setShape(class Shape *shape);

  struct Mesh *mesh;
};
#endif