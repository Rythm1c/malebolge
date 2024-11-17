#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "shape.h"

class Sphere : virtual public Shape
{
public:
    Sphere(int, int, color3f);
    ~Sphere() {}

private:
};

#endif