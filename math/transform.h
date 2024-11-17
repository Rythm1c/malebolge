#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include "vec3.h"
#include "quaternion.h"
#include "mat4.h"

class Transform
{
public:
    Transform() : translation(v3D(0.0)), orientation(Quat()), scaling(v3D(1.0)) {};
    ~Transform() {};

    v3D translation;
    Quat orientation;
    v3D scaling;

    mat4x4 get();
    Transform inverse();
   // mat4x4 toMat();
};

//Transform combine(const Transform &t1, const Transform &t2);

#endif