#include "collisions.h"
#include "../shapes/cube.h"
#include "../shapes/sphere.h"

bool intersectCubeCube(Cube *, Cube *);
bool intersectSphereCube(Sphere *, Cube *);
bool intersectSphereSphere(Sphere *, Sphere *);

bool intersect(Shape *shape1, Shape *shape2) {

  ShapeType type1 = shape1->getType();
  ShapeType type2 = shape2->getType();

  if (type1 == SHAPE_CUBE) {
    if (type2 == SHAPE_CUBE)
      return intersectCubeCube(dynamic_cast<Cube *>(shape1),
                               dynamic_cast<Cube *>(shape2));
    else
      return intersectSphereCube(dynamic_cast<Sphere *>(shape2),
                                 dynamic_cast<Cube *>(shape1));
  }
  // else if the lhs(left hand side) is a sphere bounding volume
  else {
    if (type2 == SHAPE_SPHERE)
      return intersectSphereSphere(dynamic_cast<Sphere *>(shape1),
                                   dynamic_cast<Sphere *>(shape2));
    else
      return intersectSphereCube(dynamic_cast<Sphere *>(shape1),
                                 dynamic_cast<Cube *>(shape2));
  }
}

bool intersectCubeCube(Cube *cube1, Cube *cube2) {
  BoundingBox box1 = cube1->getBoundingBox();
  BoundingBox box2 = cube2->getBoundingBox();

  bool xintersect = (box1.min.x <= box2.max.x) && (box1.max.x >= box2.min.x);
  bool yintersect = (box1.min.y <= box2.max.y) && (box1.max.y >= box2.min.y);
  bool zintersect = (box1.min.z <= box2.max.z) && (box1.max.z >= box2.min.z);

  return xintersect && yintersect && zintersect;
}

bool intersectSphereSphere(Sphere *sphere1, Sphere *sphere2) {
  float distance = get_length(sphere1->pos() - sphere2->pos());

  float totalRadii = sphere1->getRadius() + sphere2->getRadius();

  return distance <= totalRadii;
}

bool intersectSphereCube(Sphere *sphere, Cube *cube) {
  // BA=AO+BO=-OB+OA
  v3D difference = sphere->pos() - cube->pos();

  v3D dimensions = cube->getDimensions();
  v3D clamped = clamp(difference, -1.0 * dimensions, dimensions);
  v3D closestPoint = clamped + cube->pos();

  float distance = get_length(cube->pos() - closestPoint);

  return distance <= sphere->getRadius();
}
