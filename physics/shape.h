#ifndef SHAPE_H
#define SHAPE_H

#include "../math/transform.h"
#include "../math/vec3.h"

enum ShapeType
{
  SHAPE_SPHERE,
  SHAPE_CUBE
};

class Shape
{

public:
  Shape() {}
  ~Shape() {}

  virtual ShapeType getType() const = 0;
};
#endif
