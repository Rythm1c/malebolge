#ifndef PHYSICS
#define PHYSICS

#include "../math/vec3.h"
#include <iostream>

class Transform;
class Shape;

struct AABB {
  v3D min;
  v3D max;
};
class Physics {
public:
  Physics() {}
  ~Physics() {}
  // same as radius basically
  float averageSize(Transform pr_sphere);
  AABB getAABB(const v3D &pos, const v3D &size);
  // Pr_Obj: Object's properties
  void simpleGravity(v3D &v);
  // void gravity(Shape *Pr_Obj, Shape *Pr_largeMass);
  //  collision detection between 2 sphere(only primitive available)
  void cSphereVsSphere(Shape *Pr_sphere1, Shape *Pr_sphere2);
  void cSphereVsAABB(Shape *Pr_sphere, Shape *Pr_aabb);
  void cAABBVsAABB(Shape *pr_obj1, Shape *pr_obj2);
  // handle collisions
  // must be called right after checking for a collision between two spheres
};

#endif
