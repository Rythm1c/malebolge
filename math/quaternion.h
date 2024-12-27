#ifndef QUATERNION_H
#define QUATERNION_H

#include "math.h"
#include <array>
#include <iostream>

#define QUAT_EPSILON 0.000001f

struct mat4x4;
struct v3D;

struct Quat {
  union {
    struct {
      float x;
      float y;
      float z;
      float s;
    };

    float rs[4];

    std::array<float, 4> fv;
  };

  Quat() : x(0.0), y(0.0), z(0.0), s(1.0) {}
  Quat(float v) : x(v), y(v), z(v), s(v) {}
  Quat(float _x, float _y, float _z, float _s) : x(_x), y(_y), z(_z), s(_s) {}

  /// @brief creates a quaternion from an angle and specified axis
  /// @param 1: angle
  /// @param 2: axis
  Quat(float, v3D);

  float norm();
  Quat unit();
  Quat conjugate();
  Quat inverse();

  mat4x4 toMat();
};
v3D axis(Quat q);
float dot(const Quat &lhs, const Quat &rhs);
Quat mix(Quat from, Quat to, float t);

Quat operator+(const Quat &lhs, const Quat &rhs);

Quat operator*(float lhs, const Quat &rhs);
Quat operator*(const Quat lhs, float &rhs);

v3D operator*(const v3D &lhs, const Quat &rhs);
v3D operator*(const Quat &lhs, const v3D &rhs);

Quat operator*(const Quat &lhs, const Quat &rhs);

bool operator==(const Quat &left, const Quat &right);
bool operator!=(const Quat &a, const Quat &b);

#endif
