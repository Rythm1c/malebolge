#ifndef CUBE_H
#define CUBE_H

#include "shape.h"

struct BoundingBox
{
  Vector3f min;
  Vector3f max;
};

class Cube : public Shape
{
public:
  Cube(Color3f, Vector3f);
  ~Cube() {}

  ShapeType getType() const override { return SHAPE_CUBE; }

  BoundingBox getBoundingBox() const;
  Vector3f getDimensions() const { return dimensions; }

private:
  Vector3f dimensions;
};

#endif
