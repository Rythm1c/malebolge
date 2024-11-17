#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <vector>
#include "../math/vec3.h"
#include "../math/transform.h"

struct Mesh;
class Shape
{

public:
    Shape()
        : mesh(nullptr),
          color(color3f(1.0)),
          transform(Transform()),
          velocity(v3D(0.0)),
          checkered(false),
          subDivide(false),
          lines(0.0),
          divs(0.0),
          draw(true) {}
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

protected:
    Mesh *mesh;
};
#endif