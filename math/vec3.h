#ifndef VEC3_HPP
#define VEC3_HPP

#include "utils.h"
#include <array>

//  3D vector with x, y and z components
struct Vector3f
{

  union
  {
    struct
    {
      float x;
      float y;
      float z;
    };
    struct
    {
      float r; // red
      float g; // green
      float b; // blue
    };
    std::array<float, 3> v;
  };
  // default constructor with components set to 0.0
  Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}
  // set all components to a single value
  Vector3f(float _v) : x(_v), y(_v), z(_v) {}
  // use a simple array to set components
  Vector3f(float *fv) : x(fv[0]), y(fv[1]), z(fv[2]) {}
  // set each components idividually
  Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

  Vector3f operator+=(const Vector3f &r)
  {
    this->x += r.x;
    this->y += r.y;
    this->z += r.z;
    return *this;
  }
  Vector3f operator-=(const Vector3f &r)
  {
    this->x -= r.x;
    this->y -= r.y;
    this->z -= r.z;
    return *this;
  }
  Vector3f operator*=(float r)
  {
    this->x *= r;
    this->y *= r;
    this->z *= r;
    return *this;
  }
  Vector3f operator/=(float r)
  {
    this->x /= r;
    this->y /= r;
    this->z /= r;
    return *this;
  }
};
// point 3D
typedef Vector3f Point3f;
// for difining colors
typedef Vector3f Color3f;

// get the dot product between two 3D vectors
float dot(const Vector3f &p1, const Vector3f &p2);
// get the vectors/point length
float get_length(const Vector3f &v);
// get the cross product between two 3D vectors
Vector3f cross(const Vector3f &v1, const Vector3f &v2);
// normalize vec3 to have unit length
Vector3f normalize(const Vector3f &v);
// reflect vector around normal
Vector3f reflect(const Vector3f &v, const Vector3f &n);
// limit to min and max value
Vector3f clamp(const Vector3f &v, const Vector3f &min, const Vector3f &max);

Vector3f lerp(Vector3f a, Vector3f b, float c);

// miltiplication
Vector3f operator*(const Vector3f &l, float r);
Vector3f operator*(float r, const Vector3f &l);
Vector3f operator*(const Vector3f &lhs, const Vector3f &rhs);
// division
Vector3f operator/(const Vector3f &l, float r);
// addition
Vector3f operator+(const Vector3f &l, const Vector3f &r);
// subtraction
Vector3f operator-(const Vector3f &l, const Vector3f &r);
// comparisons
bool operator==(const Vector3f &l, const Vector3f &r);
bool operator!=(const Vector3f &l, const Vector3f &r);

#endif
