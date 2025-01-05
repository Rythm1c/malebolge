#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "body.h"
#include <iostream>

struct Contact
{
  Vector3f normal;
  Vector3f intersection;
  Shape *shape1;
  Shape *shape2;
};

bool intersect(Body *, Body *);
void resolveIntersection(Body *, Body *);

#endif
