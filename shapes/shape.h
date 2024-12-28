#ifndef SHAPE_H
#define SHAPE_H

#include "../math/transform.h"
#include "../math/vec3.h"
#include <iostream>
#include <vector>

enum ShapeType { SHAPE_SPHERE, SHAPE_CUBE };

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

  virtual ShapeType getType() const = 0;

  color3f color;
  bool checkered;
  bool subDivide;
  float lines;
  float divs;
  bool draw;

  Transform transform;
  v3D pos() { return this->transform.translation; }
  void translate(v3D pos) { this->transform.translation = pos; }

  Quat orientation() { return this->transform.orientation; }
  void orient(Quat orientation) { this->transform.orientation = orientation; }

  v3D velocity;
  float inverseMass;

protected:
  Mesh *mesh;
};
#endif
