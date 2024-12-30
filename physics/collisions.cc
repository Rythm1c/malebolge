#include "collisions.h"
#include "../shapes/cube.h"
#include "../shapes/sphere.h"

bool intersectCubeCube(Cube *, Cube *);
bool intersectSphereCube(Sphere *, Cube *);
bool intersectSphereSphere(Sphere *, Sphere *);

void resolveCubeCubeContact(Cube *, Cube *);
void resolveSphereCubeContact(Sphere *, Cube *);
void resolveSphereSphereContact(Sphere *, Sphere *);

bool intersect(Shape *shape1, Shape *shape2)
{

  ShapeType type1 = shape1->getType();
  ShapeType type2 = shape2->getType();

  if (type1 == SHAPE_CUBE)
  {
    if (type2 == SHAPE_CUBE)
      return intersectCubeCube(dynamic_cast<Cube *>(shape1),
                               dynamic_cast<Cube *>(shape2));
    else
      return intersectSphereCube(dynamic_cast<Sphere *>(shape2),
                                 dynamic_cast<Cube *>(shape1));
  }
  // else if the lhs(left hand side) is a sphere bounding volume
  else
  {
    if (type2 == SHAPE_SPHERE)
      return intersectSphereSphere(dynamic_cast<Sphere *>(shape1),
                                   dynamic_cast<Sphere *>(shape2));
    else
      return intersectSphereCube(dynamic_cast<Sphere *>(shape1),
                                 dynamic_cast<Cube *>(shape2));
  }
}
void resolveIntersection(Shape *shape1, Shape *shape2)
{
  ShapeType type1 = shape1->getType();
  ShapeType type2 = shape2->getType();

  if (type1 == SHAPE_CUBE)
  {
    if (type2 == SHAPE_CUBE)
      resolveCubeCubeContact(dynamic_cast<Cube *>(shape1),
                             dynamic_cast<Cube *>(shape2));
    else
      resolveSphereCubeContact(dynamic_cast<Sphere *>(shape2),
                               dynamic_cast<Cube *>(shape1));
  }
  // else if the lhs(left hand side) is a sphere
  else
  {
    if (type2 == SHAPE_SPHERE)
      resolveSphereSphereContact(dynamic_cast<Sphere *>(shape1),
                                 dynamic_cast<Sphere *>(shape2));
    else
      resolveSphereCubeContact(dynamic_cast<Sphere *>(shape1),
                               dynamic_cast<Cube *>(shape2));
  }
}
//______________________________________________________________________
bool intersectCubeCube(Cube *cube1, Cube *cube2)
{

  BoundingBox box1 = cube1->getBoundingBox();
  BoundingBox box2 = cube2->getBoundingBox();

  bool xintersect = (box1.min.x <= box2.max.x) && (box1.max.x >= box2.min.x);
  bool yintersect = (box1.min.y <= box2.max.y) && (box1.max.y >= box2.min.y);
  bool zintersect = (box1.min.z <= box2.max.z) && (box1.max.z >= box2.min.z);

  return xintersect && yintersect && zintersect;
}
void resolveCubeCubeContact(Cube *cube1, Cube *cube2)
{
  BoundingBox box1 = cube1->getBoundingBox();
  BoundingBox box2 = cube2->getBoundingBox();
  // get displacemets for each axis
  float dx1 = box1.min.x - box2.max.x;
  float dx2 = box1.max.x - box2.min.x;
  float dy1 = box1.min.y - box2.max.y;
  float dy2 = box1.max.y - box2.min.y;
  float dz1 = box1.min.z - box2.max.z;
  float dz2 = box1.max.z - box2.min.z;

  float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
  float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;
  float dz = abs(dz1) < abs(dz2) ? dz1 : dz2;

  // gets the smallest instersection per axis
  // and updates the appropriate axis with the displacement
  v3D normal = v3D(0.0);
  v3D intersection = v3D(0.0);

  if (abs(dx) < abs(dy) && abs(dx) < abs(dz))
  {
    normal = normalize(v3D(-dx, 0.0, 0.0));
    intersection = v3D(-dx, 0.0, 0.0);
  }
  else if (abs(dy) < abs(dx) && abs(dy) < abs(dz))
  {
    normal = normalize(v3D(0.0, -dy, 0.0));
    intersection = v3D(0.0, -dy, 0.0);
  }
  else
  {
    normal = normalize(v3D(0.0, 0.0, -dz));
    intersection = v3D(0.0, 0.0, -dz);
  }

  // move them outside of each other
  // and also reflect them appropriately
  // does not conserve momentum for now
  if (cube1->inverseMass != 0.0)
  {
    cube1->translate(cube1->pos() + intersection);
    cube1->velocity = 0.8 * reflect(cube1->velocity, normal);
  }

  if (cube2->inverseMass != 0.0)
  {
    cube2->translate(cube1->pos() - intersection);
    cube1->velocity = 0.8 * reflect(cube1->velocity, -1.0 * normal);
  }
}
//______________________________________________________________________
bool intersectSphereSphere(Sphere *sphere1, Sphere *sphere2)
{
  float distance = get_length(sphere1->pos() - sphere2->pos());

  float totalRadii = sphere1->getRadius() + sphere2->getRadius();

  return distance <= totalRadii;
}

void resolveSphereSphereContact(Sphere *sphere1, Sphere *sphere2)
{
  float totalRadii = sphere1->getRadius() + sphere2->getRadius();
  // get  contact normal
  // |AB| = |AO| + |OB| = |OB| - |AO|
  v3D normal = normalize(sphere2->pos() - sphere1->pos());
  // update position to remove them form each others bounding volumes
  // reduce velocities based on angle of contact with normal
  // v1 = v1 * dot(normalize(v1), -1.0 * normal);
  // v2 = v2 * dot(normalize(v2), 1.0 * normal);
  if (sphere1->inverseMass != 0.0)
  {
    sphere1->velocity = 0.8 * reflect(sphere1->velocity, -1.0 * normal);
    sphere1->translate(sphere2->pos() + totalRadii * -1.0 * normal);
  }

  if (sphere2->inverseMass != 0.0)
  {
    sphere1->velocity = 0.8 * reflect(sphere2->velocity, 1.0 * normal);
    sphere2->translate(sphere1->pos() + totalRadii * 1.0 * normal);
  }
}
//______________________________________________________________________
bool intersectSphereCube(Sphere *sphere, Cube *cube)
{
  // BA=AO+BO=-OB+OA
  v3D difference = sphere->pos() - cube->pos();

  v3D dimensions = cube->getDimensions();
  v3D clamped = clamp(difference, -1.0 * dimensions, dimensions);
  v3D closestPoint = clamped + cube->pos();

  float distance = get_length(sphere->pos() - closestPoint);

  return distance <= sphere->getRadius();
}

void resolveSphereCubeContact(Sphere *sphere, Cube *cube)
{
  v3D difference = sphere->pos() - cube->pos();

  v3D dimensions = cube->getDimensions();
  v3D clamped = clamp(difference, -1.0 * dimensions, dimensions);
  v3D closestPointCube = clamped + cube->pos();

  // BA=BO+OA=OA-OB
  v3D normal = normalize(sphere->pos() - closestPointCube);
  v3D closestPointSphere = sphere->pos() + normal * -sphere->getRadius();
  v3D intersection = closestPointSphere - closestPointCube;

  if (sphere->inverseMass != 0.0)
  {
    sphere->translate(sphere->pos() - intersection);
    sphere->velocity = 0.8 * reflect(sphere->velocity, normal);
  }

  if (cube->inverseMass != 0.0)
  {
    cube->translate(cube->pos() + intersection);
    cube->velocity = 0.8 * reflect(cube->velocity, -1.0 * normal);
  }
}
