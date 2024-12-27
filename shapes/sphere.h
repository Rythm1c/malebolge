#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include <iostream>

class Sphere : virtual public Shape {
public:
  Sphere(float, int, int, color3f);
  ~Sphere() {}

  float radius;

private:
};

#endif
