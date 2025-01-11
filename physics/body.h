#ifndef BODY_H
#define BODY_H

#include "../math/transform.h"
#include "../math/vec3.h"
#include "../math/mat3.h"

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

  Vector3f pos() const { return this->transform.translation; }
  Quat orientation() const { return this->transform.orientation; }

  void translate(Vector3f pos) { this->transform.translation = pos; }
  void orient(Quat orientation) { this->transform.orientation = orientation; }

  Vector3f velocity;
  Vector3f angularVelocity;
  float inverseMass;
  float elasticity;

  void applyImpulse(const Vector3f &pointImpulse, const Vector3f &impulse);
  void applyimpulseLinear(const Vector3f &impulse);
  void applyImpulseAngular(const Vector3f &impulse);

  class Shape *shape;
  void setShape(class Shape *shape);

  Vector3f getCenterOfMassWorldSpace() const;
  Vector3f getCenterOfMassModelSpace() const;

  Mat3x3 getInertiaTensorLocalSpace() const;
  Mat3x3 getInertiaTensorWorldSpace() const;

  struct Mesh *mesh;
};
#endif