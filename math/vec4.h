#ifndef VEC4_HPP
#define VEC4_HPP

#include "utils.h"
#include <array>

template <typename T>
struct Vector4T
{
  union
  {
    struct
    {
      T x;
      T y;
      T z;
      T w;
    };
    struct
    {
      T r; // red
      T g; // green
      T b; // blue
      T a; // alpha
    };
    std::array<T, 4> v;
  };
  // default constuctor
  inline Vector4T<T>() : x(0), y(0), z(0), w(0) {}
  // set all components to a singular value
  inline Vector4T<T>(T _v) : x(_v), y(_v), z(_v), w(_v) {}
  // set each value individialy
  inline Vector4T<T>(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
  // set the 4d vector using an array
  inline Vector4T<T>(T *_v) : x(_v[0]), y(_v[1]), z(_v[2]), w(_v[3]) {}
};
typedef Vector4T<float> Vector4f;
typedef Vector4T<int> Vector4i;
typedef Vector4T<unsigned int> Vector4ui;

typedef Vector4T<float> color4f;

#endif
