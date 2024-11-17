#ifndef LRE_MATH_HPP
#define LRE_MATH_HPP

#include <iostream>
#include <math.h>
#include <array>

#define PIE 3.141592f
#define VEC3_EPSILON 0.000001f

// convert degrees to radians
float to_radians(float degs);
// convert radians to degrees
float to_degrees(float rads);
float random_float();
float random_float(int a, int b);
int random_int(int a, int b);
float max(float a, float b);
float min(float a, float b);
// limits a value to the range min - m
template <class T>
T clamp(T v, T min, T max)
{
    if (v < min)
    {
        return min;
    }
    if (v > max)
    {
        return max;
    }
    return v;
    // return std::max(min, std::min(max, v));
}

#endif