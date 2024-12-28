#ifndef CUBE_H
#define CUBE_H

#include "shape.h"
#include <iostream>

struct BoundingBox {
  v3D min;
  v3D max;
};

class Cube : public Shape {
public:
  Cube(color3f, v3D);
  ~Cube() {}

  ShapeType getType() const override { return SHAPE_CUBE; }

  BoundingBox getBoundingBox() const;
  v3D getDimensions() const { return dimensions; }

private:
  v3D dimensions;
};

#endif
