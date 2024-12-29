#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "../shapes/shape.h"
#include <iostream>

struct Contact {
  v3D normal;
  v3D intersection;
  Shape *shape1;
  Shape *shape2;
};

bool intersect(Shape *, Shape *);
void resolveIntersection(Shape *, Shape *);

#endif
