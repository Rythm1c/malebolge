#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "shape.h"
#include <iostream>

struct Contact
{
  Vector3f normal;
  Vector3f intersection;
  Shape *shape1;
  Shape *shape2;
};

bool intersect(Shape *, Shape *);
void resolveIntersection(Shape *, Shape *);

#endif
