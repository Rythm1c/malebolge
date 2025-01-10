#ifndef SHAPE_H
#define SHAPE_H

#include "../math/transform.h"
#include "../math/vec3.h"
#include "../math/mat3.h"

enum ShapeType
{
  SHAPE_SPHERE,
  SHAPE_CUBE,
  SHAPE_CONVEX
};

class Shape
{

public:
  Shape() {}
  ~Shape() {}

  virtual ShapeType getType() const = 0;
  virtual Mat3x3 inertiaTensor() const = 0;

  virtual Vector3f getCenterOfMass() const { return centerOfMass; }

protected:
  Vector3f centerOfMass;
};
#endif
