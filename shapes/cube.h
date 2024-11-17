#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include "shape.h"

class Cube : public Shape
{
public:
    Cube(color3f, bool);
    ~Cube() {}

private:
};

#endif