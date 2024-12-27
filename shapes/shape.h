#ifndef SHAPE_H
#define SHAPE_H

#include "../math/transform.h"
#include "../math/vec3.h"
#include <iostream>
#include <vector>

// enum ShapeType { Sphere, Cube };

struct Mesh;
class Shape {

public:
  Shape()
      : color(color3f(1.0)), checkered(false), subDivide(false), lines(0.0),
        divs(0.0), draw(true), transform(Transform()), velocity(v3D(0.0)),
        inverseMass(0.0), mesh(nullptr) {}
  ~Shape() {}

  void init();
  void render();
  void clean();

  color3f color;

  bool checkered;
  bool subDivide;
  float lines;
  float divs;
  bool draw;

  Transform transform;
  v3D velocity;
  float inverseMass;

protected:
  Mesh *mesh;
};
#endif
