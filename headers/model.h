#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include "../math/vec3.h"

class Model
{
public:
    Model();
    ~Model() {}

    std::vector<struct Mesh> meshes;
    class Transform *transform;
    color3f color;

    void init();
    void render();
    void clean();
};

#endif