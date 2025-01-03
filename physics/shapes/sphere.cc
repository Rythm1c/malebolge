#include "sphere.h"
#include "../render/mesh.h"
#include "shape.h"

Sphere::Sphere(float rad) : radius(rad)
{
  this->transform.scaling = Vector3f(rad);
}
