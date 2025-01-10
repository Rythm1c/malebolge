#include "collisions.h"
#include "shapes.h"
#include "body.h"

bool intersectCubeCube(Body *, Body *);
bool intersectSphereCube(Body *, Body *);
bool intersectSphereSphere(Body *, Body *);

void resolveCubeCubeContact(Body *, Body *);
void resolveSphereCubeContact(Body *, Body *);
void resolveSphereSphereContact(Body *, Body *);

bool intersect(Body *body1, Body *body2)
{

  ShapeType typea = body1->shape->getType();
  ShapeType typeb = body2->shape->getType();

  /*  if (type1 == SHAPE_CUBE)
   {
     if (type2 == SHAPE_CUBE)
       return intersectCubeCube(body1, body2);
     else
       return intersectSphereCube(body1, body2);
   }
   // else if the lhs(left hand side) is a sphere bounding volume
   else
   {
     if (type2 == SHAPE_SPHERE)
       return intersectSphereSphere(body1, body2);
     else
       return intersectSphereCube(body1, body2);
   } */

  return intersectSphereSphere(body1, body2);
}
void resolveIntersection(Body *body1, Body *body2)
{
  ShapeType type1 = body1->shape->getType();
  ShapeType type2 = body2->shape->getType();
  /*   if (type1 == SHAPE_CUBE)
    {
      if (type2 == SHAPE_CUBE)
        resolveCubeCubeContact(body1, body2);
      else
        resolveSphereCubeContact(body1, body2);
    }
    // else if the lhs(left hand side) is a sphere
    else
    {
      if (type2 == SHAPE_SPHERE)
        resolveSphereSphereContact(body1, body2);
      else
        resolveSphereCubeContact(body1, body2);
    }*/
  return resolveSphereSphereContact(body1, body2);
}
//______________________________________________________________________
/*bool intersectCubeCube(Box *Body, Box *Body)
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
} */
//______________________________________________________________________
bool intersectSphereSphere(Body *body1, Body *body2)
{
  float distance = get_length(body1->pos() - body2->pos());

  Sphere *sphere1 = dynamic_cast<Sphere *>(body1->shape);
  Sphere *sphere2 = dynamic_cast<Sphere *>(body2->shape);

  float totalRadii = sphere1->getRadius() + sphere2->getRadius();

  return distance <= totalRadii;
}

void resolveSphereSphereContact(Body *body1, Body *body2)
{
  Sphere *sphere1 = dynamic_cast<Sphere *>(body1->shape);
  Sphere *sphere2 = dynamic_cast<Sphere *>(body2->shape);

  // |AB| = |AO| + |OB| = |OB| - |AO|
  const Vector3f normal = normalize(body1->pos() - body2->pos());
  // update position to remove them form each others bounding volumes
  Vector3f closestPtSphere1 = body1->pos() - normal * sphere1->getRadius();
  Vector3f closestPtSphere2 = body2->pos() + normal * sphere2->getRadius();

  Vector3f intersection = closestPtSphere1 - closestPtSphere2;

  const float totalInverseMass = body1->inverseMass + body2->inverseMass;

  const float ta = body1->inverseMass / (totalInverseMass);
  const float tb = body2->inverseMass / (totalInverseMass);

  const float elasticity = body1->elasticity * body2->elasticity;

  const Vector3f vab = body1->velocity - body2->velocity;
  const float impulsej = -(1.0 + elasticity) * dot(vab, 1.0 * normal) / (totalInverseMass);
  const Vector3f vectorImpulsej = -1.0 * normal * impulsej;

  body1->applyimpulseLinear(vectorImpulsej * -1.0);
  body2->applyimpulseLinear(vectorImpulsej * 1.0);

  /* body1->velocity = Vector3f(0.0);
   body2->velocity = Vector3f(0.0); */
  body1->translate(body1->pos() - intersection * ta);
  body2->translate(body2->pos() + intersection * tb);
}
//______________________________________________________________________
/* bool intersectSphereCube(Body *sphere, Body *cube)
{
  // BA=AO+BO=-OB+OA
  Vector3f difference = sphere->pos() - cube->pos();

  Vector3f dimensions = cube->getDimensions();
  Vector3f clamped = clamp(difference, -1.0 * dimensions, dimensions);
  Vector3f closestPoint = clamped + cube->pos();

  float distance = get_length(sphere->pos() - closestPoint);

  return distance <= sphere->getRadius();
} */
/*
void resolveSphereCubeContact(Body *sphere, Body *cube)
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
} */
