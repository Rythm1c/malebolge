#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include <iostream>

class Sphere : public Shape {
public:
  Sphere(float, int, int, color3f);
  ~Sphere() {}

  ShapeType getType() const override { return SHAPE_SPHERE; }

  float getRadius() const { return radius; }

private:
  float radius;
};

#endif
