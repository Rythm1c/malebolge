#include "sphere.h"

Sphere::Sphere(float rad) : radius(rad)
{
  this->centerOfMass = Vector3f(0.0);
}

Mat3x3 Sphere::inertiaTensor() const
{
  float val = 2.0 * pow(this->radius, 2.0) / 5.0;

  return Mat3x3(
      val, 0.0, 0.0,
      0.0, val, 0.0,
      0.0, 0.0, val);
}
