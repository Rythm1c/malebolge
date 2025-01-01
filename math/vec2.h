#ifndef VEC2_HPP
#define VEC2_HPP

#include "utils.h"
#include <array>

template <typename T>
struct Vector2T
{
  union
  {
    struct
    {
      T x;
      T y;
    };
    std::array<T, 2> v;
  };
  // default constructor
  Vector2T() : x(0), y(0) {}
  // set all components to a single value
  Vector2T(T _v) : x(_v), y(_v) {}
  // set values individually
  Vector2T(T _x, T _y) : x(_x), y(_y) {}
  // set values using array
  Vector2T(T *_v) : x(_v[0]), y(_v[1]) {}
};

typedef Vector2T<float> Point2f;
typedef Vector2T<float> Vector2f;
typedef Vector2T<int> Vector2i;
typedef Vector2T<unsigned int> Vector2ui;

Vector2i step(Vector2f a, Vector2f b);

bool operator==(const Vector2f &l, const Vector2f &r);

#endif
