#include "collisions.h"
#include "shapes.h"

bool intersectCubeCube(Box *, Box *);
bool intersectSphereCube(Sphere *, Box *);
bool intersectSphereSphere(Sphere *, Sphere *);

void resolveCubeCubeContact(Box *, Box *);
void resolveSphereCubeContact(Sphere *, Box *);
void resolveSphereSphereContact(Sphere *, Sphere *);

bool intersect(Shape *shape1, Shape *shape2)
{

  ShapeType type1 = shape1->getType();
  ShapeType type2 = shape2->getType();

  if (type1 == SHAPE_CUBE)
  {
    if (type2 == SHAPE_CUBE)
      return intersectCubeCube(dynamic_cast<Box *>(shape1),
                               dynamic_cast<Box *>(shape2));
    else
      return intersectSphereCube(dynamic_cast<Sphere *>(shape2),
                                 dynamic_cast<Box *>(shape1));
  }
  // else if the lhs(left hand side) is a sphere bounding volume
  else
  {
    if (type2 == SHAPE_SPHERE)
      return intersectSphereSphere(dynamic_cast<Sphere *>(shape1),
                                   dynamic_cast<Sphere *>(shape2));
    else
      return intersectSphereCube(dynamic_cast<Sphere *>(shape1),
                                 dynamic_cast<Box *>(shape2));
  }
}
void resolveIntersection(Shape *shape1, Shape *shape2)
{
  ShapeType type1 = shape1->getType();
  ShapeType type2 = shape2->getType();

  if (type1 == SHAPE_CUBE)
  {
    if (type2 == SHAPE_CUBE)
      resolveCubeCubeContact(dynamic_cast<Box *>(shape1),
                             dynamic_cast<Box *>(shape2));
    else
      resolveSphereCubeContact(dynamic_cast<Sphere *>(shape2),
                               dynamic_cast<Box *>(shape1));
  }
  // else if the lhs(left hand side) is a sphere
  else
  {
    if (type2 == SHAPE_SPHERE)
      resolveSphereSphereContact(dynamic_cast<Sphere *>(shape1),
                                 dynamic_cast<Sphere *>(shape2));
    else
      resolveSphereCubeContact(dynamic_cast<Sphere *>(shape1),
                               dynamic_cast<Box *>(shape2));
  }
}
//______________________________________________________________________
bool intersectCubeCube(Box *cube1, Box *cube2)
{

  BoundingBox box1 = cube1->getBounds();
  BoundingBox box2 = cube2->getBounds();

  bool xintersect = (box1.min.x <= box2.max.x) && (box1.max.x >= box2.min.x);
  bool yintersect = (box1.min.y <= box2.max.y) && (box1.max.y >= box2.min.y);
  bool zintersect = (box1.min.z <= box2.max.z) && (box1.max.z >= box2.min.z);

  return xintersect && yintersect && zintersect;
}
void resolveCubeCubeContact(Box *cube1, Box *cube2)
{
  BoundingBox box1 = cube1->getBounds();
  BoundingBox box2 = cube2->getBounds();
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
  Vector3f normal = Vector3f(0.0);
  Vector3f intersection = Vector3f(0.0);

  if (abs(dx) < abs(dy) && abs(dx) < abs(dz))
  {
    normal = normalize(Vector3f(-dx, 0.0, 0.0));
    intersection = Vector3f(-dx, 0.0, 0.0);
  }
  else if (abs(dy) < abs(dx) && abs(dy) < abs(dz))
  {
    normal = normalize(Vector3f(0.0, -dy, 0.0));
    intersection = Vector3f(0.0, -dy, 0.0);
  }
  else
  {
    normal = normalize(Vector3f(0.0, 0.0, -dz));
    intersection = Vector3f(0.0, 0.0, -dz);
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
  Vector3f normal = normalize(sphere2->pos() - sphere1->pos());
  // update position to remove them form each others bounding volumes
  Vector3f closestPtSphere1 = sphere1->pos() + normal * sphere1->getRadius();
  Vector3f closestPtSphere2 = sphere2->pos() - normal * sphere2->getRadius();

  Vector3f intersection = closestPtSphere1 - closestPtSphere2;

  if (sphere1->inverseMass != 0.0)
  {
    sphere1->velocity = 0.8 * reflect(sphere1->velocity, -1.0 * normal);
    sphere1->translate(sphere2->pos() + intersection);
  }

  if (sphere2->inverseMass != 0.0)
  {
    sphere1->velocity = 0.8 * reflect(sphere2->velocity, 1.0 * normal);
    sphere2->translate(sphere1->pos() - intersection);
  }
}
//______________________________________________________________________
bool intersectSphereCube(Sphere *sphere, Box *cube)
{
  // BA=AO+BO=-OB+OA
  Vector3f difference = sphere->pos() - cube->pos();

  Vector3f dimensions = cube->getDimensions();
  Vector3f clamped = clamp(difference, -1.0 * dimensions, dimensions);
  Vector3f closestPoint = clamped + cube->pos();

  float distance = get_length(sphere->pos() - closestPoint);

  return distance <= sphere->getRadius();
}

void resolveSphereCubeContact(Sphere *sphere, Box *cube)
{
  Vector3f difference = sphere->pos() - cube->pos();

  Vector3f dimensions = cube->getDimensions();
  Vector3f clamped = clamp(difference, -1.0 * dimensions, dimensions);
  Vector3f closestPointCube = clamped + cube->pos();

  // BA=BO+OA=OA-OB
  Vector3f normal = normalize(sphere->pos() - closestPointCube);
  Vector3f closestPointSphere = sphere->pos() + normal * -sphere->getRadius();
  Vector3f intersection = closestPointSphere - closestPointCube;

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
