#include "sphere.h"

Sphere::Sphere(float rad) : radius(rad)
{
  this->transform.scaling = Vector3f(rad);
}
