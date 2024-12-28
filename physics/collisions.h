#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <iostream>

bool intersect(class Shape *, class Shape *);

bool intersectCubeCube(class Cube *, class Cube *);
bool intersectSphereCube(class Sphere *, class Cube *);
bool intersectSphereSphere(class Sphere *, class Sphere *);

#endif
