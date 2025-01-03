#ifndef BOX_H
#define BOX_H

#include "../shape.h"

struct BoundingBox
{
  Vector3f min;
  Vector3f max;
};

class Box : public Shape
{
public:
  Box(Vector3f);
  ~Box() {}

  ShapeType getType() const override { return SHAPE_CUBE; }

  BoundingBox getBounds() const;
  Vector3f getDimensions() const { return dimensions; }

private:
  Vector3f dimensions;
};

#endif
