#ifndef VEC3_HPP
#define VEC3_HPP

#include "math.h"

//  3D vector with x, y and z components
struct v3D
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
    v3D() : x(0.0f), y(0.0f), z(0.0f) {}
    // set all components to a single value
    v3D(float _v) : x(_v), y(_v), z(_v) {}
    // use a simple array to set components
    v3D(float *fv) : x(fv[0]), y(fv[1]), z(fv[2]) {}
    // set each components idividually
    v3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    v3D operator+=(const v3D &r)
    {
        this->x += r.x;
        this->y += r.y;
        this->z += r.z;
        return *this;
    }
    v3D operator-=(const v3D &r)
    {
        this->x -= r.x;
        this->y -= r.y;
        this->z -= r.z;
        return *this;
    }
    v3D operator*=(float r)
    {
        this->x *= r;
        this->y *= r;
        this->z *= r;
        return *this;
    }
    v3D operator/=(float r)
    {
        this->x /= r;
        this->y /= r;
        this->z /= r;
        return *this;
    }
};
// point 3D
typedef v3D p3D;
// for difining colors
typedef v3D color3f;

// get the dot product between two 3D vectors
float dot(const v3D &p1, const v3D &p2);
// get the vectors/point length
float get_length(const v3D &v);
// get the cross product between two 3D vectors
v3D cross(const v3D &v1, const v3D &v2);
// normalize vec3 to have unit length
v3D normalize(const v3D &v);
// reflect vector around normal
v3D reflect(const v3D &v, const v3D &n);
// limit to min and max value
v3D clamp(const v3D &v, const v3D &min, const v3D &max);

v3D lerp(v3D a, v3D b, float c);

// miltiplication
v3D operator*(const v3D &l, float r);
v3D operator*(float r, const v3D &l);
v3D operator*(const v3D &lhs, const v3D &rhs);
// division
v3D operator/(const v3D &l, float r);
// addition
v3D operator+(const v3D &l, const v3D &r);
// subtraction
v3D operator-(const v3D &l, const v3D &r);
// comparisons
bool operator==(const v3D &l, const v3D &r);
bool operator!=(const v3D &l, const v3D &r);

#endif