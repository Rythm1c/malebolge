#ifndef CUBE_H
#define CUBE_H

#include "shape.h"
#include <iostream>

class Cube : public Shape {
public:
  Cube(color3f, bool);
  ~Cube() {}

private:
};

#endif
