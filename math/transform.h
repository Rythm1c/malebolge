#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat4.h"
#include "quaternion.h"
#include "vec3.h"
#include <iostream>

class Transform {
public:
  Transform()
      : translation(v3D(0.0)), orientation(Quat()), scaling(v3D(1.0)) {};
  ~Transform() {};

  v3D translation;
  Quat orientation;
  v3D scaling;

  /// @brief combines the translation, rotation and scaling members to produce a
  /// transformation matrix
  /// @return finall transform matrix
  mat4x4 get();
  Transform inverse();
};

Transform combine(const Transform &t1, const Transform &t2);
Transform transformFromMat(mat4x4 &mat);

#endif
