#ifndef VEC2_HPP
#define VEC2_HPP

#include "math.h"

template <typename T>
struct Tvector2D
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
    Tvector2D() : x(0), y(0) {}
    // set all components to a single value
    Tvector2D(T _v) : x(_v), y(_v) {}
    // set values individually
    Tvector2D(T _x, T _y) : x(_x), y(_y) {}
    // set values usinf array
    Tvector2D(T *_v) : x(_v[0]), y(_v[1]) {}
};

typedef Tvector2D<float> p2D;
typedef Tvector2D<float> v2D;
typedef Tvector2D<int> iv2D;
typedef Tvector2D<unsigned int> uiv2D;

bool operator==(const v2D &l, const v2D &r);

#endif